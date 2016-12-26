from test import *
import tool as tool
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.externals import joblib
import tensorflow as tf

ABS_PATH = "/home/elvis/work/ML/tensorflow/separa/"

SIZE = 4746
# SIZE = 3312

LABEL = 5
TRAIN_SIZE = 768
ACCELERATION_FACTOR = 2048
BASE_DIVIDE = 256
# TRAIN_SIZE = 3200
BATCH_SIZE = 512
GLOBAL_STEP = 200000000
DECAY_STEPS = 10000
EVAL_SIZE = SIZE - TRAIN_SIZE
# IMAGE_SIZE = 645 - 60
IMAGE_SIZE = 64
NUM_CHANNEL = 1
REPORT_CONTROL = 500
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 0.01
# REGULAR = 3e-3
REGULAR = 3e-3
DROP_OUT = 8.0e-1
DECAY_RATE = 0.9995
MOMENTUM = 95e-2
SEED = random.random() * 1000
BATCH_NORMALIZATION = 1e-3
MODEL = "lda-svm.model"


# SEED = 295.730694719
# SEED = 935.121374578
# SEED = 149.555544719
# SEED = 266.751015428 pretty good for this data .
# SEED = 571.684134972


def batch_normalization(x, depth, phase_train):
    shape = x.get_shape()
    beta = tf.Variable(tf.constant(0.0, shape=[depth]),
                       name='beta', trainable=True)
    gamma = tf.Variable(tf.constant(1.0, shape=[depth]),
                        name='gamma', trainable=True)
    if len(shape) == 4:
        batch_mean, batch_var = tf.nn.moments(x, [0, 1, 2], name='moments')
    else:
        batch_mean, batch_var = tf.nn.moments(x, [0], name='moments')
    ema = tf.train.ExponentialMovingAverage(decay=0.5)

    def mean_var_with_update():
        ema_apply_op = ema.apply([batch_mean, batch_var])
        with tf.control_dependencies([ema_apply_op]):
            return tf.identity(batch_mean), tf.identity(batch_var)

    flag = tf.Variable(initial_value=phase_train, dtype=tf.bool)
    mean, var = tf.cond(flag, mean_var_with_update, lambda: (ema.average(batch_mean), ema.average(batch_var)))
    normed = tf.nn.batch_normalization(x, mean, var, beta, gamma, BATCH_NORMALIZATION)
    return normed


def main(argv=None):
    if argv is None:
        print ("ERROR FOR ARGV IS NONE")
    else:
        print (argv)

    global SIZE, TRAIN_SIZE

    data, label, fileset = parse_new_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)

    print (label[0])
    mat_show(data[0])

    print (label[1])
    mat_show(data[1])

    print (label[-1])
    mat_show(data[-1])

    data, label = alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)

    data = tool.min_max_normalization(data)

    SIZE = label.shape[0]

    data = np.reshape(data, [SIZE, -1])

    TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
    EVAL_SIZE = SIZE - TRAIN_SIZE

    train_data, train_label, eval_data, eval_label = tool.random_sample(data, label, ACCELERATION_FACTOR, LABEL)

    train_data, train_label = tool.random_shuffle(train_data, train_label)
    eval_data, eval_label = tool.random_shuffle(eval_data, eval_label)

    print (train_label)

    print ("lda ready")

    """
    lda = LinearDiscriminantAnalysis()
    lda.fit(train_data, np.argmax(train_label, 1))
    joblib.dump(lda, "lda-mlp.model")
    """

    lda = joblib.load(MODEL)

    print ("lda done")

    train_out = lda.predict(train_data)
    eval_out = lda.predict(eval_data)

    train_temp = np.argmax(train_label, 1)
    eval_temp = np.argmax(eval_label, 1)

    print (np.sum(train_out == train_temp) / float(TRAIN_SIZE))
    print (np.sum(eval_out == eval_temp) / float(EVAL_SIZE))

    train_data = lda.transform(train_data)

    eval_data = lda.transform(eval_data)

    TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
    EVAL_SIZE = SIZE - TRAIN_SIZE

    train_data = min_max_normalization(train_data)
    eval_data = min_max_normalization(eval_data)

    print ("ALL SIZE FOR %d " % SIZE)
    print ("TRAIN SIZE FOR %d " % TRAIN_SIZE)

    feed_eval_data = tf.placeholder(dtype=tf.float32, shape=[None, LABEL - 1], name="feed_eval_data")
    feed_eval_label = tf.placeholder(dtype=tf.int8, shape=[None, LABEL], name="feed_eval_label")

    feed_train_data = tf.placeholder(dtype=tf.float32, shape=[None, LABEL - 1], name="feed_train_data")
    feed_train_label = tf.placeholder(dtype=tf.int8, shape=[None, LABEL], name="feed_train_label")

    fc1_weights = tf.Variable(
        initial_value=tf.truncated_normal(shape=[LABEL - 1, 16], stddev=0.1, dtype=tf.float32, seed=SEED), name="fc1")

    fc1_biases = tf.Variable(initial_value=tf.truncated_normal(shape=[16], stddev=0.1, dtype=tf.float32, seed=SEED),
                             name="bias1")

    fc2_weights = tf.Variable(
        initial_value=tf.truncated_normal(shape=[16, 10], stddev=0.1, seed=SEED, dtype=tf.float32), name="fc2")

    fc2_biases = tf.Variable(initial_value=tf.truncated_normal(shape=[10], stddev=0.1, dtype=tf.float32, seed=SEED),
                             name="bias2")

    fc3_weights = tf.Variable(initial_value=tf.truncated_normal(shape=[10, LABEL], stddev=0.1, dtype=tf.float32,
                                                                seed=SEED), name="fc3")

    fc3_biases = tf.Variable(initial_value=tf.truncated_normal(shape=[LABEL], stddev=0.1, dtype=tf.float32, seed=SEED),
                             name="bias3")

    def forward(info=None, flag=False):

        # info = tf.reshape(info, [-1, LABEL - 1])
        fc = tf.reshape(info, [-1, fc1_weights.get_shape().as_list()[0]])

        hidden = tf.matmul(fc, fc1_weights) + fc1_biases

        # hidden_bn = batch_normalization(x=hidden, depth=hidden.get_shape()[-1], phase_train=flag)

        hidden_sigmoid = tf.nn.sigmoid(hidden)

        hidden_2 = tf.matmul(a=hidden_sigmoid, b=fc2_weights) + fc2_biases

        # hidden_2_bn = batch_normalization(x=hidden_2, depth=hidden_2.get_shape()[-1], phase_train=flag)

        hidden_2_relu = tf.nn.relu(hidden_2)

        hidden_3 = tf.matmul(a=hidden_2_relu, b=fc3_weights) + fc3_biases

        network = hidden_3

        return network

    logits = forward(feed_train_data, True)

    train_predict = tf.nn.softmax(logits)

    loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits, feed_train_label))

    # loss = tf.reduce_mean(-tf.reduce_sum(feed_train_label * tf.log(train_predict), reduction_indices=[1]))

    regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases) +
                    tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(fc2_biases) +
                    tf.nn.l2_loss(fc3_weights) + tf.nn.l2_loss(fc3_biases))

    loss += REGULAR * regularizers

    eval_logits = forward(feed_eval_data, False)

    eval_predict = tf.nn.softmax(eval_logits)

    eval_loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(eval_logits, feed_eval_label))

    # eval_loss = tf.reduce_mean(-tf.reduce_sum(feed_eval_label * tf.log(eval_predict), reduction_indices=[1]))

    TENSOR_GLOBAL_STEP = tf.Variable(0, dtype=tf.int64)

    learning_rate = tf.train.exponential_decay(
        LEARNING_RATE,  # Base learning rate.
        TENSOR_GLOBAL_STEP,  # Current index into the dataset.
        DECAY_STEPS,  # Decay step.
        DECAY_RATE,  # Decay rate.
        staircase=True)

    # optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(loss=loss)
    # optimizer = tf.train.RMSPropOptimizer(learning_rate=learning_rate, decay=DECAY_RATE).minimize(loss)

    # optimizer = tf.train.MomentumOptimizer(learning_rate=learning_rate,
    #                                        momentum=MOMENTUM).minimize(loss=loss,
    #                                                                   global_step=TENSOR_GLOBAL_STEP)

    # optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(loss)

    optimizer = tf.train.AdagradOptimizer(learning_rate=learning_rate).minimize(loss=loss)
    # optimizer = tf.train.FtrlOptimizer(learning_rate=learning_rate).minimize(loss)

    with tf.Session() as sess:
        print ("INIT.")
        print (SEED)

        init = tf.global_variables_initializer()
        sess.run(init)

        tf.summary.scalar(name="learning", tensor=learning_rate)
        tf.summary.histogram(name="learning", values=learning_rate)

        tf.summary.scalar(name="regularizers", tensor=regularizers * REGULAR)
        tf.summary.histogram(name="regularizers", values=regularizers * REGULAR)

        tf.summary.scalar(name="loss", tensor=loss - REGULAR * regularizers)
        tf.summary.histogram(name="loss", values=loss - REGULAR * regularizers)

        tf.summary.scalar(name="eval_loss", tensor=eval_loss)
        tf.summary.histogram(name="eval_loss", values=eval_loss)

        merge_op = tf.summary.merge_all()

        train_writer = tf.summary.FileWriter(logdir="./log/train/", graph=sess.graph)
        valid_writer = tf.summary.FileWriter(logdir="./log/valid/", graph=sess.graph)

        train_data_reshape = train_data
        train_label_reshape = train_label

        limit = TRAIN_SIZE // BATCH_SIZE + 1
        limit_eval = EVAL_SIZE // BATCH_SIZE + 1

        acc_loss = 1000

        while acc_loss > 0.2:
            for step in range(GLOBAL_STEP):
                if step % REPORT_CONTROL == 0:

                    print ("STEP %d " % step)
                    print ("------------------------------------>")

                    for batch in range(limit_eval):
                        print ("EVAL BATCH SIZE FOR %d " % batch)
                        if batch == limit_eval - 1:
                            start = batch * BATCH_SIZE
                            end = EVAL_SIZE
                            if end - start == 0:
                                continue
                        else:
                            start = batch * BATCH_SIZE
                            end = start + BATCH_SIZE

                        input = eval_data[start:end]
                        input_label = eval_label[start:end]

                        feed_dict = {feed_eval_data: input.astype(float),
                                     feed_eval_label: input_label}

                        _eval_predict, _eval_loss, _regularizers = sess.run(
                            [eval_predict, eval_loss, regularizers],
                            feed_dict=feed_dict)

                        media = np.argmax(_eval_predict, 1)
                        array = np.argmax(input_label, 1)

                        acc_sum = np.sum(media == array)
                        accurate = (acc_sum / float(end - start))

                        acc_loss = _eval_loss
                        _regularizers *= REGULAR

                        print (media)
                        print (array)

                        print ("accurate %f " % accurate)
                        print ("loss %f " % _eval_loss)
                        print ("regularizers %f " % _regularizers)
                        print ("------------------------------------>")

                        # _merge = sess.run([merge_op], feed_dict=feed_dict)
                        # train_writer.add_run_metadata(_merge, step)
                        # train_writer.add_event(_merge)

                for batch in range(limit):
                    if batch == limit - 1:
                        start = batch * BATCH_SIZE
                        end = TRAIN_SIZE
                        if end - start == 0:
                            continue
                    else:
                        start = batch * BATCH_SIZE
                        end = start + BATCH_SIZE

                    input = train_data[start:end]
                    input_label = train_label[start:end]

                    feed_dict = {feed_train_data: input.astype(float),
                                 feed_train_label: input_label}

                    _loss, _optimizer, _train_predict, _regular, _learn_rate = sess.run(
                        [loss, optimizer, train_predict, regularizers, learning_rate],
                        feed_dict=feed_dict)

                    _adjust_regular = _regular * np.float16(REGULAR)

                    media = np.argmax(_train_predict, 1)
                    array = np.argmax(input_label, 1)

                    temp = np.sum(media == array)

                    if step % REPORT_CONTROL == 0:
                        accurate = (temp / float(end - start))

                        print ("loss %f" % _loss)
                        print ("regular %f" % _adjust_regular)
                        print ("accurate %f " % accurate)
                        print ("learn_rate %f " % _learn_rate)

                        # _merge = sess.run([merge_op], feed_dict=feed_dict)
                        # train_writer.add_summary(_merge)

    return


if '__main__' == __name__:
    tf.app.run()
