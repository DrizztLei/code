from test import *
import tensorflow as tf

ABS_PATH = "/home/elvis/work/ML/tensorflow/separa/"

SIZE = 4746
# SIZE = 3312

LABEL = 5
TRAIN_SIZE = 768
ACCELERATION_FACTOR = 2048
BASE_DIVIDE = 256
# TRAIN_SIZE = 3200
BATCH_SIZE = 1024
GLOBAL_STEP = 200000000
DECAY_STEPS = 100
EVAL_SIZE = SIZE - TRAIN_SIZE
# IMAGE_SIZE = 645 - 60
IMAGE_SIZE = 224
NUM_CHANNEL = 1
REPORT_CONTROL = 15
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 0.001
# REGULAR = 3e-3
REGULAR = 2e-3
DROP_OUT = 8.0e-1
DECAY_RATE = 0.9995
MOMENTUM = 50e-2
SEED = random.random() * 1000
BATCH_NORMALIZATION = 1e-3


# SEED = 295.730694719
# SEED = 935.121374578
# SEED = 149.555544719
# SEED = 266.751015428 pretty good for this data .


def process_data_label():
    data, label = parse_new_data(SIZE=SIZE, IMAGE_SIZE=IMAGE_SIZE, NUM_CHANNEL=NUM_CHANNEL, LABEL=LABEL,
                                 BASE_DIVIDE=BASE_DIVIDE)

    data, label = alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)

    return data, label


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
    global SIZE

    data, label, fileset = parse_new_data(SIZE=SIZE, IMAGE_SIZE=IMAGE_SIZE, NUM_CHANNEL=NUM_CHANNEL, LABEL=LABEL,
                                          BASE_DIVIDE=BASE_DIVIDE)

    print (fileset[0])
    print (label[0])
    # mat_show(data[0])

    print (fileset[1])
    print (label[1])
    # mat_show(data[1])

    print (fileset[-1])
    print (label[-1])
    # mat_show(data[-1])

    SIZE = label.shape[0]

    data, label = alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)

    data = min_max_normalization(data)

    train_data, train_label, eval_data, eval_label = random_sample(data, label, ACCELERATION_FACTOR, LABEL)

    TRAIN_SIZE = train_label.shape[0]
    EVAL_SIZE = eval_label.shape[0]

    train_data, train_label = random_shuffle(train_data, train_label)
    eval_data, eval_label = random_shuffle(eval_data, eval_label)

    train_data = train_data.astype(np.float32)
    eval_data = eval_data.astype(np.float32)

    train_label = train_label.astype(np.int64)
    eval_label = eval_label.astype(np.int64)

    print ("ALL SIZE FOR %d " % SIZE)
    print ("TRAIN SIZE FOR %d " % TRAIN_SIZE)

    feed_eval_data = tf.placeholder(dtype=tf.float32, shape=[None, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL],
                                    name="feed_eval_data")
    feed_eval_label = tf.placeholder(dtype=tf.int64, shape=[None, LABEL], name="feed_eval_label")

    feed_train_data = tf.placeholder(dtype=tf.float32, shape=[None, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL],
                                     name="feed_train_data")

    feed_train_label = tf.placeholder(dtype=tf.int64, shape=[None, LABEL], name="feed_train_label")

    convolution_weights = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, NUM_CHANNEL, 5], seed=SEED,
                                                                        stddev=0.01, dtype=tf.float32))

    convolution_biases = tf.Variable(initial_value=tf.zeros(shape=[5], dtype=tf.float32))

    convolution_weights2 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 5, 10], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases2 = tf.Variable(initial_value=tf.zeros(shape=[10], dtype=tf.float32))

    convolution_weights3 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 10, 3], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases3 = tf.Variable(initial_value=tf.zeros(shape=[3], dtype=tf.float32))

    convolution_weights4 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 3, 1], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases4 = tf.Variable(initial_value=tf.zeros(shape=[1], dtype=tf.float32))

    convolution_weights5 = tf.Variable(initial_value=tf.truncated_normal(shape=[4, 4, 20, 10], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases5 = tf.Variable(initial_value=tf.zeros(shape=[10], dtype=tf.float32))

    convolution_weights6 = tf.Variable(initial_value=tf.truncated_normal(shape=[4, 4, 20, 10], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases6 = tf.Variable(initial_value=tf.zeros(shape=[10], dtype=tf.float32))

    convolution_weights7 = tf.Variable(initial_value=tf.truncated_normal(shape=[4, 4, 20, 10], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases7 = tf.Variable(initial_value=tf.zeros(shape=[10], dtype=tf.float32))

    fc1_weights = tf.Variable(
        initial_value=tf.truncated_normal(shape=[9, 18], stddev=1, seed=SEED, dtype=tf.float32))

    fc1_biases = tf.Variable(initial_value=tf.truncated_normal(shape=[18], stddev=1, seed=SEED, dtype=tf.float32))

    fc2_weights = tf.Variable(
        initial_value=tf.truncated_normal(shape=[18, 5], stddev=1, seed=SEED, dtype=tf.float32))

    fc2_biases = tf.Variable(initial_value=tf.truncated_normal(shape=[5], stddev=1, seed=SEED, dtype=tf.float32))

    fc3_weights = tf.Variable(initial_value=tf.constant(shape=[30, 5], value=0.01, dtype=tf.float32))

    fc3_biases = tf.Variable(initial_value=tf.constant(shape=[5], value=0.01, dtype=tf.float32))

    def forward(info=None, flag=False):
        info = tf.reshape(info, [-1, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])

        conv1 = tf.nn.conv2d(input=info,
                             filter=convolution_weights,
                             padding="VALID",
                             strides=[1, 2, 2, 1])

        # conv1_bn = batch_normalization(x=conv1, depth=conv1.get_shape()[-1], phase_train=flag)

        conv1_relu = tf.nn.relu(tf.nn.bias_add(conv1, convolution_biases))

        pool = tf.nn.max_pool(value=conv1_relu,
                              ksize=[1, 2, 2, 1],
                              strides=[1, 2, 2, 1],
                              padding="SAME")

        conv2 = tf.nn.conv2d(input=pool,
                             strides=[1, 2, 2, 1],
                             padding="VALID",
                             filter=convolution_weights2)

        # conv2_bn = batch_normalization(x=conv2, depth=conv2.get_shape()[-1], phase_train=flag)

        relu2 = tf.nn.relu(tf.nn.bias_add(conv2, convolution_biases2))

        pool2 = tf.nn.avg_pool(value=relu2,
                               ksize=[1, 2, 2, 1],
                               strides=[1, 2, 2, 1],
                               padding="SAME")

        conv3 = tf.nn.conv2d(input=pool2,
                             strides=[1, 2, 2, 1],
                             padding="VALID",
                             filter=convolution_weights3)

        relu3 = tf.nn.relu(tf.nn.bias_add(conv3, convolution_biases3))

        conv4 = tf.nn.conv2d(input=relu3,
                             strides=[1, 2, 2, 1],
                             padding="VALID",
                             filter=convolution_weights4)

        relu4 = tf.nn.relu(tf.nn.bias_add(conv4, convolution_biases4))

        """
        print (relu4.get_shape())
        raw_input()
        """

        fc = tf.reshape(relu4, [-1, fc1_weights.get_shape().as_list()[0]])

        # fc = batch_normalization(fc, depth=fc.get_shape()[-1], phase_train=flag)

        hidden = tf.matmul(fc, fc1_weights) + fc1_biases

        hidden_relu = tf.nn.relu(hidden)

        hidden_2 = tf.matmul(a=hidden_relu, b=fc2_weights) + fc2_biases

        if flag:
            hidden_2 = tf.nn.dropout(hidden_2, DROP_OUT, seed=SEED)

        network = hidden_2
        return network

    logits = forward(feed_train_data, True)

    """
    loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(
        logits, feed_train_label))
    """

    loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits, feed_train_label))

    regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases) +
                    tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(fc2_biases))

    # loss += REGULAR * regularizers
    train_predict = tf.nn.softmax(logits)

    eval_logits = forward(feed_eval_data, False)

    """
    eval_loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(
        eval_logits, feed_eval_label))
    """

    eval_loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(eval_logits, feed_eval_label))

    eval_predict = tf.nn.softmax(eval_logits)

    TENSOR_GLOBAL_STEP = tf.Variable(0, dtype=tf.int64)
    learning_rate = tf.train.exponential_decay(
        LEARNING_RATE,  # Base learning rate.
        TENSOR_GLOBAL_STEP,  # Current index into the dataset.
        DECAY_STEPS,  # Decay step.
        DECAY_RATE,  # Decay rate.
        staircase=True)

    optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(loss=loss)
    # optimizer = tf.train.RMSPropOptimizer(learning_rate=learning_rate, decay=DECAY_RATE).minimize(loss)
    # optimizer = tf.train.MomentumOptimizer(learning_rate=learning_rate,
    #                                       momentum=MOMENTUM).minimize(loss=loss,
    #                                                                   global_step=TENSOR_GLOBAL_STEP)
    # optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(loss)
    # optimizer = tf.train.AdagradOptimizer(learning_rate=learning_rate).minimize(loss=eval_loss)
    # optimizer = tf.train.FtrlOptimizer(learning_rate=learning_rate).minimize(loss)
    # optimizer = tf.train.ProximalGradientDescentOptimizer(learning_rate).minimize(loss)

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
        valid_writer = tf.summary.FileWriter(logdir="./log/valid")

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
                        print ("loss %f " % (float(_eval_loss) - float(_regularizers)))
                        print ("regularizers %f " % _regularizers)
                        print ("------------------------------------>")

                for batch in xrange(limit):

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

                    feed_dict = {feed_train_data: input,
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
                        print ("batch for %d " % batch)
                        print ("loss %f" % (float(_loss) - float(_adjust_regular)))
                        print ("regular %f" % _adjust_regular)
                        print ("accurate %f " % accurate)
                        print ("learn_rate %f " % _learn_rate)

                        # meta = tf.RunMetadata()
                        # train_writer.add_run_metadata(meta, str(step) + "_" + str(batch))
                        # info = sess.run([merge_op], feed_dict=feed_dict)
                        # train_writer.add_summary(info, step)
    return


if '__main__' == __name__:
    tf.app.run()
