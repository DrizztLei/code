import tensorflow as tf

import cv2 as cv
import numpy as np
import time as te
import random

from tensorflow.contrib.graph_editor import ph

from test import *

ABS_PATH = "/home/visualization/work/ML/tensorflow/separa/"

SIZE = 828
# SIZE = 3312

LABEL = 6
TRAIN_SIZE = 768
# TRAIN_SIZE = 3200
BATCH_SIZE = 2048
GLOBAL_STEP = 20000000000
DECAY_STEPS = 100
EVAL_SIZE = SIZE - TRAIN_SIZE
IMAGE_SIZE = 28
NUM_CHANNEL = 1
REPORT_CONTROL = 200
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 8.6e-5
# REGULAR = 3e-3
REGULAR = 0.0
DROP_OUT = 1.0
DECAY_RATE = 1.0
MOMENTUM = 50-2
SEED = random.random() * 1000
BATCH_NORMALIZATION = 1e-3

# SEED = 295.730694719
# SEED = 935.121374578
# SEED = 149.555544719
# SEED = 266.751015428 pretty good for this data .

def cv_read(name):
    convert_name = ABS_PATH+str(name)
    img = cv.imread(filename=convert_name)
    img = (img[...,...,0:1])
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
    data, label = parse_data(SIZE=SIZE, IMAGE_SIZE=IMAGE_SIZE, NUM_CHANNEL=NUM_CHANNEL, LABEL=LABEL)
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

    data, label = process_data_label()
    SIZE = label.shape[0]
    TRAIN_SIZE = SIZE - ACCELERATION_FACTOR

    print ("ALL SIZE FOR %d " % SIZE)
    print ("TRAIN SIZE FOR %d " % TRAIN_SIZE)

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

    train_data, train_label, eval_data, eval_label = random_sample(data, label, ACCELERATION_FACTOR)

    """
    train_data = data[0:TRAIN_SIZE, ::, ::, ::]
    train_label = label[0:TRAIN_SIZE]
    train_label = train_label.astype(dtype=np.int64)

    eval_data = (np.reshape(a=np.reshape(a=data, newshape=[LABEL, SIZE / LABEL, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
    [..., TRAIN_SLICE::, ..., ..., ...],
                            newshape=[EVAL_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL]))
    eval_label = (np.reshape(a=np.reshape(a=label, newshape=[LABEL, SIZE / LABEL])[..., TRAIN_SLICE::],
                             newshape=[EVAL_SIZE]))
    eval_label = eval_label.astype(dtype=np.int64)
    eval_label -= 1
    eval_data = data[TRAIN_SIZE:SIZE, ::, ::, ::]
    eval_label = label[TRAIN_SIZE:SIZE]
    eval_label = eval_label.astype(dtype=np.int64)
    """

    feed_train_data = tf.placeholder(tf.float32, [None, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
    feed_train_label = tf.placeholder(tf.int64, [None, LABEL])

    feed_eval_data = tf.placeholder(dtype=tf.float32, shape=[None, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
    feed_eval_label = tf.placeholder(dtype=tf.int64, shape=[None, LABEL])

    convolution_weights = tf.Variable(initial_value=tf.truncated_normal(shape=[4, 4, NUM_CHANNEL, 50], seed=SEED,
                                                                        stddev=0.01, dtype=tf.float32))

    convolution_biases = tf.Variable(initial_value=tf.zeros(shape=[50], dtype=tf.float32))

    convolution_weights2 = tf.Variable(initial_value=tf.truncated_normal(shape=[4, 4, 50, 30], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases2 = tf.Variable(initial_value=tf.zeros(shape=[30], dtype=tf.float32))

    convolution_weights3 = tf.Variable(initial_value=tf.truncated_normal(shape=[4, 4, 30, 20], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases3 = tf.Variable(initial_value=tf.zeros(shape=[20], dtype=tf.float32))

    convolution_weights4 = tf.Variable(initial_value=tf.truncated_normal(shape=[4, 4, 20, 10], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32))

    convolution_biases4 = tf.Variable(initial_value=tf.zeros(shape=[10], dtype=tf.float32))

    fc1_weights = tf.Variable(
        initial_value=tf.constant(shape=[784, 130], value=0.1, dtype=tf.float32))

    fc1_biases = tf.Variable(initial_value=tf.constant(shape=[130], value=0.01, dtype=tf.float32))

    fc2_weights = tf.Variable(
        initial_value=tf.constant(shape=[130, 21], value=0.01, dtype=tf.float32))

    fc2_biases = tf.Variable(initial_value=tf.constant(shape=[21], value=0.01, dtype=tf.float32))

    fc3_weights = tf.Variable(initial_value=tf.constant(shape=[21,6], value=0.01, dtype=tf.float32))

    fc3_biases = tf.Variable(initial_value=tf.constant(shape=[6], value=0.01, dtype=tf.float32))

    def forward(info=None, flag=False):
        info = tf.reshape(info, [-1, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])

        """
        conv = tf.nn.conv2d(input=info,
                            filter=convolution_weights,
                            padding="VALID",
                            strides=[1, 4, 4, 1])

        conv_bn = batch_normalization(x=conv, depth=conv.get_shape()[-1], phase_train=flag)

        relu = tf.nn.relu(tf.nn.bias_add(conv_bn, convolution_biases))

        pool = tf.nn.max_pool(value=relu,
                              ksize=[1, 2, 2, 1],
                              strides=[1, 2, 2, 1],
                              padding="SAME")

        conv2 = tf.nn.conv2d(input=pool,
                             strides=[1, 4, 4, 1],
                             padding="VALID",
                             filter=convolution_weights2)

        conv2_bn = batch_normalization(x=conv2, depth=conv2.get_shape()[-1], phase_train=flag)

        relu2 = tf.nn.relu(tf.nn.bias_add(conv2_bn, convolution_biases2))

        pool2 = tf.nn.max_pool(value=relu2,
                               ksize=[1, 2, 2, 1],
                               padding="SAME",
                               strides=[1, 2, 2, 1])
        """

        """
        conv3 = tf.nn.conv2d(input=pool2,
                             strides=[1, 2, 2, 1],
                             filter=convolution_weights3,
                             padding='VALID')

        conv3_bn = batch_normalization(x=conv3, depth=conv3.get_shape()[-1], phase_train=flag)

        relu3 = tf.nn.relu(tf.nn.bias_add(value=conv3_bn, bias=convolution_biases3))

        pool3 = tf.nn.max_pool(value=relu3,
                               ksize=[1, 2, 2, 1],
                               strides=[1, 2, 2, 1],
                               padding='SAME')

        conv4 = tf.nn.conv2d(input=pool3,
                             filter=convolution_weights4,
                             padding='VALID',
                             strides=[1, 1, 1, 1])

        conv4_bn = batch_normalization(x=conv4, depth=conv4.get_shape()[-1], phase_train=flag)

        relu4 = tf.nn.relu(tf.nn.bias_add(value=conv4_bn, bias=convolution_biases4))

        pool4 = tf.nn.avg_pool(value=relu4,
                               ksize=[1, 2, 2, 1],
                               strides=[1, 2, 2, 1],
                               padding='SAME')

        fc = tf.reshape(pool4, [-1, fc1_weights.get_shape().as_list()[0]])
        """

        print (info.get_shape())

        fc = tf.reshape(info, [-1, fc1_weights.get_shape().as_list()[0]])

        hidden_1 = tf.matmul(a=fc, b=fc1_weights) + fc1_biases

        hidden_1_bn = batch_normalization(x=hidden_1, depth=hidden_1.get_shape()[-1], phase_train=flag)

        hidden_1_relu = tf.nn.relu(hidden_1_bn)

        hidden_2 = tf.matmul(a=hidden_1_relu, b=fc2_weights) + fc2_biases

        hidden_2_bn = batch_normalization(x=hidden_2, depth=hidden_2.get_shape()[-1], phase_train=flag)

        hidden_2_relu = tf.nn.relu(hidden_2_bn)

        if flag:
            network = tf.nn.dropout(hidden_2_relu, DROP_OUT, seed=SEED)
        network = tf.matmul(hidden_2_relu, fc3_weights) + fc3_biases

        return network

    logist = forward(feed_train_data, True)
    loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logist, feed_train_label))
    regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases) +
                    tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(fc2_biases))
    loss += REGULAR * regularizers
    train_predict = tf.nn.softmax(logist)

    TENSOR_GLOBAL_STEP = tf.Variable(0, dtype=tf.int64)
    learning_rate = tf.train.exponential_decay(
        LEARNING_RATE,  # Base learning rate.
        TENSOR_GLOBAL_STEP,  # Current index into the dataset.
        DECAY_STEPS,  # Decay step.
        DECAY_RATE,  # Decay rate.
        staircase=True)

    # optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(loss=loss)
    # optimizer = tf.train.RMSPropOptimizer(learning_rate=learning_rate, decay=DECAY_RATE).minimize(loss)
    # optimizer = tf.train.MomentumOptimizer(learning_rate=learning_rate, momentum=MOMENTUM).minimize(loss=loss, global_step=TENSOR_GLOBAL_STEP)
    optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(loss)
    # optimizer = tf.train.AdagradOptimizer(learning_rate=learning_rate).minimize(loss=loss)

    eval_logist = forward(feed_eval_data, False)
    eval_loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(eval_logist, feed_eval_label))
    eval_predict = tf.nn.softmax(eval_logist)

    with tf.Session() as sess:
        print ("INIT.")
        print (SEED)
        init = tf.initialize_all_variables()
        sess.run(init)

        tf.histogram_summary(tag="learning", values=learning_rate)
        tf.histogram_summary(tag="regularizers", values=regularizers * REGULAR)
        tf.histogram_summary(tag="loss", values=loss - REGULAR * regularizers)
        summer = tf.train.SummaryWriter(logdir="./log", graph=sess.graph)

        merge = tf.merge_all_summaries()

        train_data_reshape = train_data
        train_label_reshape = train_label

        limit = TRAIN_SIZE // BATCH_SIZE + 1

        for step in xrange(GLOBAL_STEP):
            if step % REPORT_CONTROL == 0:
                print ("step for %d " % step)
            for batch in xrange(limit):
                start = end = 0
                if batch == limit - 1:
                    start = batch * BATCH_SIZE
                    end = TRAIN_SIZE
                else:
                    start = batch * BATCH_SIZE
                    end = start + BATCH_SIZE

                input = train_data_reshape[start:end]
                input_label = train_label_reshape[start:end]

                feed_dict = {feed_train_data: input,
                             feed_train_label: input_label}

                _loss, _optimizer, _train_predict, _regular, _learn_rate = sess.run([loss, optimizer, train_predict, regularizers, learning_rate],
                                                                                    feed_dict=feed_dict)
                _adjust_regular = _regular * np.float32(REGULAR)

                media = (np.argmax(_train_predict, 1))
                array = (np.argmax(input_label, 1))

                temp = np.sum(media == array)

                if step % REPORT_CONTROL == 0:
                    print ("loss %f" % _loss)
                    print ("regular %f" % _adjust_regular)
                    accurate = (temp / float(end - start))
                    summary = sess.run([merge], feed_dict=feed_dict)
                    print ("accurate %f " % accurate)
                    print ("learn_rate %f " % _learn_rate)
                    # _merge = sess.run(merge, feed_dict=feed_dict)
            if step % REPORT_CONTROL == 0:
                start = 0
                end = BATCH_SIZE
                print ("EVAL")
                input = eval_data
                input_label = eval_label

                feed_dict = {feed_eval_data: input,
                             feed_eval_label: input_label}

                _eval_predict, _eval_loss = sess.run([eval_predict, eval_loss], feed_dict=feed_dict)

                media = (np.argmax(_eval_predict, 1))
                array = (np.argmax(input_label, 1))

                temp = np.sum(media == array)
                accurate = (temp / float(end - start))
                print (media)
                # print ("EVALING")
                print ("accurate %f " % accurate)
                print ("loss %f " % _eval_loss)
    return


if '__main__' == __name__:
    tf.app.run()
