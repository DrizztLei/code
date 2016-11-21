import tensorflow as tf

import cv2 as cv
import numpy as np
import time as te

from parse import *

ABS_PATH="/home/visualization/work/ML/tensorflow/separa/"

SIZE = 828
LABEL = 6
TRAIN_SIZE = 768
BATCH_SIZE = 128
GLOBAL_STEP = 20000
DECAY_STEPS = 10
EVAL_SIZE = SIZE - TRAIN_SIZE
IMAGE_SIZE = 128
NUM_CHANNEL = 3
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 4e-2
REGULAR = 1.2e-3
DECAY_RATE = 95e-2
SEED = None
DROP_OUT = 0.86
MOMENTUM = 0.4


def img_show(img):
    cv.namedWindow("IMG")
    while True:
        cv.imshow("IMG", img)
        character = cv.waitKey(100)
        if int(character) == 'a': break


def cv_read(name):
    convert_name = ABS_PATH+str(name)
    img = cv.imread(filename=convert_name)
    img = (img[...,...,0:1])
    # print (img)
    img = cv.resize(src=img, dsize=(IMAGE_SIZE, IMAGE_SIZE))
    return img


def read(file_name):
    info = np.loadtxt(fname=file_name, dtype=str, delimiter=';')

    return_data = []

    data = info[..., 0]
    label = info[..., 1]

    for i in xrange(len(data)):
        return_data.append(pretreatment(data[i]).reshape(IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL))

    return np.array(return_data), np.array(label)


def pretreatment(name):
    return cv_read(name=name)


def rotation(img):
    print ("ROTATION")
    # cv.getRotationMatrix2D(center=, angle=, scale=)


def process_data_label():
    get_file_name()
    data, label = parse_data()
    return data, label


def main(argv=None):
    if argv is None:
        print ("ERROR FOR ARGV IS NONE")
    else:
        print (argv)

    data, label = process_data_label()

    """
    train_data = (np.reshape(a=np.reshape(a=data,
                                          newshape=[LABEL, SIZE / LABEL, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
    [..., 0:TRAIN_SLICE, ..., ..., ...],
                             newshape=[TRAIN_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL]))

    train_label = (np.reshape(a=(np.reshape(a=label,
                                            newshape=[LABEL, SIZE / LABEL])
                                 [..., 0:TRAIN_SLICE]),
                              newshape=[TRAIN_SIZE]))
    """

    train_data = data[0:TRAIN_SIZE, ::, ::, ::]
    # img_show(train_data[0])
    train_label = label[0:TRAIN_SIZE]
    train_label = train_label.astype(dtype=np.int64)

    """
    eval_data = (np.reshape(a=np.reshape(a=data, newshape=[LABEL, SIZE / LABEL, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
    [..., TRAIN_SLICE::, ..., ..., ...],
                            newshape=[EVAL_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL]))
    eval_label = (np.reshape(a=np.reshape(a=label, newshape=[LABEL, SIZE / LABEL])[..., TRAIN_SLICE::],
                             newshape=[EVAL_SIZE]))
    eval_label = eval_label.astype(dtype=np.int64)
    eval_label -= 1
    """

    eval_data = data[TRAIN_SIZE:SIZE, ::, ::, ::]
    eval_label = label[TRAIN_SIZE:SIZE]

    feed_train_data = tf.placeholder(dtype=tf.float32, shape=[BATCH_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
    # feed_train_label = tf.placeholder(dtype=tf.int64, shape=[BATCH_SIZE, LABEL])
    feed_train_label = tf.placeholder(dtype=tf.int64, shape=[BATCH_SIZE])

    feed_eval_data = tf.placeholder(dtype=tf.float32, shape=[SIZE - TRAIN_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
    feed_eval_label = tf.placeholder(dtype=tf.int64, shape=[SIZE - TRAIN_SIZE])

    convolution_weights = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, NUM_CHANNEL, 50], seed=SEED,
                                                                        stddev=0.01, dtype=tf.float32))

    convolution_biases = tf.Variable(initial_value=tf.zeros(shape=[50], dtype=tf.float32))

    convolution_weights2 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 50, 30], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases2 = tf.Variable(initial_value=tf.zeros(shape=[30], dtype=tf.float32))

    convolution_weights3 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 30, 20], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases3 = tf.Variable(initial_value=tf.zeros(shape=[20], dtype=tf.float32))

    convolution_weights4 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 20, 10], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases4 = tf.Variable(initial_value=tf.zeros(shape=[10], dtype=tf.float32))

    fc1_weights = tf.Variable(
        initial_value=tf.constant(shape=[640 , 256], value=0.1, dtype=tf.float32))

    fc1_biases = tf.Variable(initial_value=tf.constant(shape=[256], value=0.01, dtype=tf.float32))

    fc2_weights = tf.Variable(
        initial_value=tf.constant(shape=[256, 6], value=0.1, dtype=tf.float32))

    fc2_biases = tf.Variable(initial_value=tf.constant(shape=[6], value=0.01, dtype=tf.float32))

    def forward(info=None, flag=False):
        conv = tf.nn.conv2d(input=info,
                            filter=convolution_weights,
                            padding="VALID",
                            strides=[1, 1, 1, 1])

        relu = tf.nn.relu(tf.nn.bias_add(conv, convolution_biases))

        pool = tf.nn.max_pool(value=relu,
                              ksize=[1, 2, 2, 1],
                              strides=[1, 2, 2, 1],
                              padding="SAME")

        conv2 = tf.nn.conv2d(input=pool,
                             strides=[1, 1, 1, 1],
                             padding="VALID",
                             filter=convolution_weights2)

        relu2 = tf.nn.relu(tf.nn.bias_add(conv2, convolution_biases2))

        pool2 = tf.nn.max_pool(value=relu2,
                               ksize=[1, 2, 2, 1],
                               padding="SAME",
                               strides=[1, 2, 2, 1])

        conv3 = tf.nn.conv2d(input=pool2,
                             filter=convolution_weights3,
                             padding='VALID',
                             strides=[1, 1, 1, 1])

        relu3 = tf.nn.relu(tf.nn.bias_add(value=conv3, bias=convolution_biases3))

        pool3 = tf.nn.max_pool(value=relu3,
                               ksize=[1, 2, 2, 1],
                               strides=[1, 2, 2, 1],
                               padding='SAME')

        pool2 = tf.nn.max_pool(value=relu2,
                               ksize=[1, 2, 2, 1],
                               padding="SAME",
                               strides=[1, 2, 2, 1])

        conv3 = tf.nn.conv2d(input=pool2,
                             filter=convolution_weights3,
                             padding='VALID',
                             strides=[1, 1, 1, 1])

        relu3 = tf.nn.relu(tf.nn.bias_add(value=conv3, bias=convolution_biases3))

        pool3 = tf.nn.max_pool(value=relu3,
                               ksize=[1, 2, 2, 1],
                               strides=[1, 2, 2, 1],
                               padding='SAME')

        conv4 = tf.nn.conv2d(input=pool3,
                             filter=convolution_weights4,
                             padding='VALID',
                             strides=[1, 1, 1, 1])

        relu4 = tf.nn.relu(tf.nn.bias_add(value=conv4, bias=convolution_biases4))

        pool4 = tf.nn.avg_pool(value=relu4,
                               ksize=[1, 2, 2, 1],
                               strides=[1, 2, 2, 1],
                               padding='SAME')

        pool_shape = pool4.get_shape().as_list()
        print (pool_shape)
        reshape = tf.reshape(shape=[pool_shape[0], pool_shape[1] * pool_shape[2] * pool_shape[3]], tensor=pool4)

        hidden = tf.nn.relu(tf.matmul(a=reshape, b=fc1_weights) + fc1_biases)

        if flag:
            hidden = tf.nn.dropout(x=tf.nn.relu(tf.matmul(hidden, fc2_weights) + fc2_biases), keep_prob=DROP_OUT,
                                   seed=SEED)
        else:
            hidden = tf.nn.relu(tf.matmul(hidden, fc2_weights) + fc2_biases)
        return hidden

    logist = forward(feed_train_data, True)

    cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=logist, labels=feed_train_label)

    loss = tf.reduce_mean(cross_entropy, reduction_indices=0)

    """
    for i in xrange(feed_train_label.get_shape()[0]):
        print (out.get_shape())
        value = out[i][feed_train_label[i]]
        loss += -tf.log(value)
        out[i][feed_train_label[i]] -= 1
    """

    regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases) +
                    tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(fc2_biases)
                    +
                    tf.nn.l2_loss(convolution_weights4) + tf.nn.l2_loss(convolution_biases4) +
                    tf.nn.l2_loss(convolution_weights3) + tf.nn.l2_loss(convolution_biases3) +
                    tf.nn.l2_loss(convolution_weights2) + tf.nn.l2_loss(convolution_biases2) +
                    tf.nn.l2_loss(convolution_weights) + tf.nn.l2_loss(convolution_biases))

    loss += REGULAR * regularizers

    # op = tf.Print(loss, [loss], message='loss : ')

    TENSOR_GLOBAL_STEP = tf.Variable(0, dtype=tf.int64)
    learning_rate = tf.train.exponential_decay(
        LEARNING_RATE,  # Base learning rate.
        TENSOR_GLOBAL_STEP,  # Current index into the dataset.
        DECAY_STEPS,  # Decay step.
        DECAY_RATE,  # Decay rate.
        staircase=True)

    # optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate, name="Gradient_Descent_Optimzer").minimize(loss=loss)
    optimizer = tf.train.MomentumOptimizer(learning_rate=learning_rate, momentum=MOMENTUM).minimize(loss=loss, global_step=TENSOR_GLOBAL_STEP)
    # optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(loss)

    train_predict = forward(feed_train_data)

    # eval_predict = tf.nn.softmax(forward(feed_eval_data, False))
    # saver = tf.train.Saver()

    with tf.Session() as sess:
        print ("INIT.")
        init = tf.initialize_all_variables()
        sess.run(init)

        tf.histogram_summary(tag="learning", values=learning_rate)
        tf.histogram_summary(tag="regularizers", values=regularizers * REGULAR)
        tf.histogram_summary(tag="loss", values=loss - REGULAR * regularizers)

        summer = tf.train.SummaryWriter(logdir="./log", graph=sess.graph)
        merge = tf.merge_all_summaries()

        train_data_reshape = train_data
        train_label_reshape = train_label

        for step in xrange(GLOBAL_STEP):

            all_batch = TRAIN_SIZE // BATCH_SIZE
            rate = float(BATCH_SIZE) / TRAIN_SIZE
            unit = TRAIN_SIZE / LABEL
            flag = True
            for batch in xrange(TRAIN_SIZE // BATCH_SIZE):
                start = batch * BATCH_SIZE
                end = start + BATCH_SIZE

                input = train_data_reshape[start:end, ..., ..., ...]
                input_label = train_label_reshape[start:end]

                feed_dict = {feed_train_data: input,
                             feed_train_label: input_label}
                # sess.run(optimizer, feed_dict=feed_dict)
                # _optimizer, _loss, _train_predict = sess.run(fetches=[merge, optimizer, loss, train_predict],
                #                                             feed_dict=feed_dict)
                _loss = sess.run(loss, feed_dict=feed_dict)
                _optimizer = sess.run(optimizer, feed_dict=feed_dict)
                # print (_optimizer)
                _regular = sess.run(regularizers, feed_dict=feed_dict)
                _adjust_regular = _regular * np.float32(REGULAR)

                _train_predict = sess.run(train_predict, feed_dict=feed_dict)
                media = np.argmax(a=_train_predict, axis=1)
                array = feed_dict[feed_train_label]
                temp = np.sum(media == array) / float(BATCH_SIZE)

                _learn_rate = sess.run(learning_rate)

                """
                _merge, _optimizer, _loss, _learning_rate, _train_predict = sess.run(
                    fetches=[merge, optimizer, loss, learning_rate, train_predict],
                    feed_dict=feed_dict)

                array = feed_dict[feed_train_label]
                array = array.astype(dtype=np.int64)
                media = np.argmax(a=_train_predict, axis=1).astype(dtype=np.int64)
                temp = np.sum(media == array) / float(BATCH_SIZE)
                """

                if step % 10 == 0:
                    """
                        _merge, _loss, _learning_rate, _train_predict = sess.run(
                            fetches=[merge, loss, learning_rate, train_predict],
                            feed_dict=feed_dict)

                    _loss, _learning_rate, _train_predict = sess.run(
                            fetches=[loss, learning_rate, train_predict],
                            feed_dict=feed_dict)
                    array = feed_dict[feed_train_label]
                    array = array.astype(dtype=np.int64)
                    media = np.argmax(a=_train_predict, axis=1).astype(dtype=np.int64)
                    temp = np.sum(media == array) / float(BATCH_SIZE)

                    print ('accuracy : %.3f' % temp)
                    print ('loss : %.4f' % _loss)
                    """

                    print ("loss %f" % _loss)
                    print ("regular %f" % _adjust_regular)
                    print ("accurate %f " % temp)
                    print ("learn_rate %f " % _learn_rate)
                    # print (media[56:94])
                    # print (input_label[56:94])
                    _merge = sess.run(merge, feed_dict=feed_dict)

    return


if '__main__' == __name__:
    tf.app.run()
