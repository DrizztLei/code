from test import *
import tensorflow as tf
from scipy import interp
import matplotlib.pyplot as plt
from sklearn.metrics import roc_curve, auc

from sklearn.cross_validation import StratifiedKFold

ABS_PATH = "/home/elvis/work/ML/tensorflow/separa/"
PREFIX = "/home/elvis/work/ML/tensorflow/separa/"
SUFIX =  "alexnet-train-acc-0.998046875-loss-0.00772435776889.ckpt"
MODEL = PREFIX + SUFIX

# SIZE = 4746
SIZE = 311

# LABEL = 5
LABEL = 6

# ACCELERATION_FACTOR = 256
ACCELERATION_FACTOR = 2048
BASE_DIVIDE = 2048
# TRAIN_SIZE = 3200
BATCH_SIZE = 311
GLOBAL_STEP = 200000000
DECAY_STEPS = 100
# IMAGE_SIZE = 645 - 60
IMAGE_SIZE = 227
NUM_CHANNEL = 3
REPORT_CONTROL = 10

LEARNING_RATE = 0.001
# REGULAR = 3e-3
REGULAR = 3e-4
DROP_OUT = 80e-2
DECAY_RATE = 0.9995
MOMENTUM = 99e-2
SEED = int(random.random() * 1000)
BATCH_NORMALIZATION = 1e-3


def main(argv=None):
    if argv is None:
        print ("ERROR FOR ARGV IS NONE")
    else:
        print (argv)
    global SIZE

    data, label, fileset = parse_roc_auc(SIZE=SIZE, IMAGE_SIZE=IMAGE_SIZE, NUM_CHANNEL=NUM_CHANNEL, LABEL=LABEL,
                                         BASE_DIVIDE=BASE_DIVIDE)

    print (data.shape)
    print (data.dtype)

    print (fileset[0])
    print (label[0])

    print (fileset[1])
    print (label[1])

    print (fileset[-1])
    print (label[-1])

    SIZE = label.shape[0]

    print ("z-score ing")
    data = approximate_normalization(data)
    print ("z-score done")

    print ("random shuffling")
    data, label = random_shuffle(data, label)
    print ("random shuffle done")

    data = data.astype(np.float32)
    label = label.astype(np.int64)

    feed_eval_data = tf.placeholder(dtype=tf.float32, shape=[None, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL],
                                    name="feed_eval_data")
    feed_eval_label = tf.placeholder(dtype=tf.int64, shape=[None, LABEL], name="feed_eval_label")

    convolution_weights_1 = tf.Variable(initial_value=tf.truncated_normal(shape=[11, 11, NUM_CHANNEL, 96], seed=SEED,
                                                                          stddev=0.01, dtype=tf.float32), name="conv1")

    convolution_biases_1 = tf.Variable(initial_value=tf.zeros(shape=[96], dtype=tf.float32), name="conv1_bias")

    convolution_weights2 = tf.Variable(initial_value=tf.truncated_normal(shape=[5, 5, 96, 256], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32), name="conv2")

    convolution_biases2 = tf.Variable(initial_value=tf.zeros(shape=[256], dtype=tf.float32), name="conv2_bias")

    convolution_weights3 = tf.Variable(initial_value=tf.truncated_normal(shape=[3, 3, 256, 384], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32), name="conv3")

    convolution_biases3 = tf.Variable(initial_value=tf.zeros(shape=[384], dtype=tf.float32), name="conv3_bias")

    convolution_weights4 = tf.Variable(initial_value=tf.truncated_normal(shape=[3, 3, 384, 384], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32), name="conv4")

    convolution_biases4 = tf.Variable(initial_value=tf.zeros(shape=[384], dtype=tf.float32), name="conv4_bias")

    convolution_weights5 = tf.Variable(initial_value=tf.truncated_normal(shape=[3, 3, 384, 256], seed=SEED,
                                                                         stddev=0.01, dtype=tf.float32), name="conv5")

    convolution_biases5 = tf.Variable(initial_value=tf.zeros(shape=[256], dtype=tf.float32), name="conv5_bias")

    fc1_weights = tf.Variable(
        initial_value=tf.truncated_normal(shape=[9216, 4096], stddev=0.01, seed=SEED, dtype=tf.float32), name="fc1")

    fc1_biases = tf.Variable(initial_value=tf.zeros(shape=[4096], dtype=tf.float32), name="fc1_bias")

    fc2_weights = tf.Variable(
        initial_value=tf.truncated_normal(shape=[4096, 4096], stddev=0.01, seed=SEED, dtype=tf.float32), name="fc2")

    fc2_biases = tf.Variable(initial_value=tf.zeros(shape=[4096], dtype=tf.float32), name="fc2_bias")

    fc3_weights = tf.Variable(
        initial_value=tf.truncated_normal(shape=[4096, LABEL], stddev=0.01, seed=SEED, dtype=tf.float32), name="fc3")

    # fc3_biases = tf.Variable(initial_value=tf.zeros(shape=[5], dtype=tf.float32))

    def forward(info=None, flag=False):

        info = tf.reshape(info, [-1, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])

        print (info.get_shape())

        conv1 = tf.nn.conv2d(input=info,
                             filter=convolution_weights_1,
                             padding="VALID",
                             strides=[1, 4, 4, 1])

        print (conv1.get_shape())

        # conv1_bn = batch_normalization(x=conv1, depth=conv1.get_shape()[-1], phase_train=flag)

        relu1 = tf.nn.relu(tf.nn.bias_add(conv1, convolution_biases_1))

        print (relu1.get_shape())

        pool1 = tf.nn.avg_pool(value=relu1,
                               ksize=[1, 3, 3, 1],
                               strides=[1, 2, 2, 1],
                               padding="VALID")

        print (pool1.get_shape())

        norm1 = tf.nn.local_response_normalization(pool1)

        # norm1 = batch_norm(pool1, flag)

        print (norm1.get_shape())

        conv2 = tf.nn.conv2d(input=norm1,
                             strides=[1, 1, 1, 1],
                             padding="SAME",
                             filter=convolution_weights2)

        # tf.nn.batch_normalization()

        # conv2_bn = batch_normalization(x=conv2, depth=conv2.get_shape()[-1], phase_train=flag)

        print (conv2.get_shape())

        relu2 = tf.nn.relu(tf.nn.bias_add(conv2, convolution_biases2))

        print (relu2.get_shape())

        pool2 = tf.nn.max_pool(value=relu2,
                               ksize=[1, 3, 3, 1],
                               strides=[1, 2, 2, 1],
                               padding="VALID")

        print (pool2.get_shape())

        norm2 = tf.nn.local_response_normalization(pool2)

        # norm2 = batch_norm(pool2, flag)

        print (norm2.get_shape())

        conv3 = tf.nn.conv2d(input=norm2,
                             strides=[1, 1, 1, 1],
                             padding="SAME",
                             filter=convolution_weights3)

        print (conv3.get_shape())

        relu3 = tf.nn.relu(tf.nn.bias_add(conv3, convolution_biases3))

        print (relu3.get_shape())

        conv4 = tf.nn.conv2d(input=relu3,
                             strides=[1, 1, 1, 1],
                             padding="SAME",
                             filter=convolution_weights4)

        print (conv4.get_shape())

        relu4 = tf.nn.relu(tf.nn.bias_add(conv4, convolution_biases4))

        print (relu4.get_shape())

        conv5 = tf.nn.conv2d(input=relu4,
                             strides=[1, 1, 1, 1],
                             padding="SAME",
                             filter=convolution_weights5)

        print (conv5.get_shape())

        relu5 = tf.nn.relu(tf.nn.bias_add(conv5, convolution_biases5))

        print (relu5.get_shape())

        pool5 = tf.nn.max_pool(value=relu5,
                               ksize=[1, 3, 3, 1],
                               strides=[1, 2, 2, 1],
                               padding="VALID")

        fc = tf.reshape(pool5, [-1, fc1_weights.get_shape().as_list()[0]])

        # fc = batch_normalization(fc, depth=fc.get_shape()[-1], phase_train=flag)

        hidden_1 = tf.matmul(fc, fc1_weights) + fc1_biases

        hidden_1_relu = tf.nn.relu(hidden_1)

        # hidden_1_relu_bn = batch_norm(hidden_1_relu, flag)

        if flag:
            hidden_1_relu = tf.nn.dropout(hidden_1_relu, keep_prob=DROP_OUT)

        hidden_2 = tf.matmul(a=hidden_1_relu, b=fc2_weights) + fc2_biases

        hidden_2_relu = tf.nn.relu(hidden_2)

        hidden_2_relu_bn = batch_norm(hidden_2_relu, flag)

        if flag:
            hidden_2_relu_bn = tf.nn.dropout(hidden_2_relu_bn, keep_prob=DROP_OUT)

        hidden_3 = tf.matmul(hidden_2_relu_bn, fc3_weights)

        network = hidden_3

        return network

    eval_logits = forward(feed_eval_data, False)

    eval_loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(eval_logits, feed_eval_label))

    eval_predict = tf.nn.softmax(eval_logits)

    regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases) +
                    tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(fc2_biases) +
                    tf.nn.l2_loss(fc3_weights))

    saver = tf.train.Saver()

    with tf.Session() as sess:
        print ("model loading")

        saver.restore(sess, MODEL)

        print ("model loaded")

        limit = SIZE // BATCH_SIZE

        MID = 2

        for batch in range(limit + 1):
            start = batch * BATCH_SIZE
            end = start + BATCH_SIZE

            if start >= SIZE:
                continue
            if end > SIZE:
                end = SIZE

            eval_data = data[start:end]
            eval_label = label[start:end]

            feed_dict = {feed_eval_data: eval_data}

            _eval_predict = sess.run([eval_predict], feed_dict)

            _eval_predict = np.array(_eval_predict).reshape([end - start, -1])

            mean_tpr = 0.0
            mean_fpr = np.linspace(0, 1, 100)

            prob_ = np.ndarray([end - start])

            auc_label = np.ndarray([end - start])
            actually_label = np.ndarray([end - start])
            validation = np.argmax(eval_label, 1)

            result = np.ndarray([end-start])

            for y in range(eval_label.shape[0]):

                score_non_sep = np.sum(_eval_predict[y, 0:3])
                score_sep = np.sum(_eval_predict[y, 3::])

                if score_non_sep > score_sep:
                    actually_label[y] = 0
                    prob_[y] = 1 - score_non_sep
                    result[y] = 0
                else:
                    actually_label[y] = 1
                    prob_[y] = score_sep
                    result[y] = 1

                goal = validation[y]

                if goal > MID:
                    auc_label[y] = 1
                else:
                    auc_label[y] = 0

            print ("acc for %f" % float(np.sum(auc_label == result) / float((end - start))))

            fpr, tpr, thresholds = roc_curve(auc_label, prob_)

            mean_tpr += interp(mean_fpr, fpr, tpr)

            mean_tpr[0] = 0.0

            roc_auc = auc(fpr, tpr)

            plt.plot(fpr, tpr, lw=1, label='ROC (area = %0.2f)' % roc_auc)

            plt.plot([0, 1], [0, 1], '--', color=(0.6, 0.6, 0.6), label='random_guess')

            """
            plt.plot(mean_fpr, mean_tpr, 'k--',
                     label='Mean ROC (area = %0.2f)' % mean_auc, lw=2)
            """

            plt.xlim([-0.05, 1.05])
            plt.ylim([-0.05, 1.05])

            plt.xlabel('False Positive Rate')
            plt.ylabel('True Positive Rate')

            plt.title('Receiver Operating Characteristic')

            plt.legend(loc="lower right")

            plt.show()

    return


if '__main__' == __name__:
    tf.app.run()
