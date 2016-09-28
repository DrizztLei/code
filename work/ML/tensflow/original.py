import tensorflow as tf
import numpy as np
import cv2 as cv

NUM_EPOCHS = 30000
BATCH_SIZE = 0
EVAL_BATCH_SIZE = 100
SEED = 1000
NUM_LABELS = 40
REGULAR_RATE = 5e-4
IMAGE_SIZE = 28
NUMCHANNELS = 3


def readCSV(filename):
    info = np.loadtxt(filename , dtype=str , delimiter=";")
    train = info[::,0]
    label = info[::,1]
    return train , label

def average(value):
    return (value[0] * 0.30 + value[1] * 0.59 + value[2] * 0.11) / 3

def read(filename):

    '''
    return tf.image.convert_image_dtype(
        tf.image.decode_png(
            tf.read_file(
                filename) , channels=3 ) , dtype=tf.uint8)
    '''
    temp = cv.cvtColor(cv.imread(filename) , cv.COLOR_RGB2GRAY)
    out = cv.resize(temp , (IMAGE_SIZE , IMAGE_SIZE))
    return out

def main(argv=None):

    info , label = readCSV("./read.csv")

    train_data = []
    valida_data = []
    train_label = []
    valida_label = []
    num_epochs = NUM_EPOCHS

    '''
    for x in xrange(img.shape[0]):
        for y in xrange(img.shape[1]):
            value = average(img[x][y])
            picture[x][y] = value
    print picture
    picture = cv.cvtColor(img , cv.COLOR_BGR2GRAY)
    print picture.shape
    '''

    length = len(info)
    for i in xrange(length):
        if (i+1) % 10 < 2 :
            valida_data.append(read(info[i]))
            valida_label.append(label[i])
        else:
            train_data.append(read(info[i]))
            train_label.append(info[i])

    train_size = len(train_data)

    BATCH_SIZE = train_size
    IMG_Y = train_data[0].shape[0]
    IMG_X = train_data[0].shape[1]

    train_data_node = tf.placeholder(tf.float32 ,
                                     shape=(BATCH_SIZE , IMG_Y , IMG_X , NUMCHANNELS))

    train_label_node = tf.placeholder(tf.int32 ,
                                      shape=(BATCH_SIZE,))

    eval_data = tf.placeholder(tf.float32 ,
                               shape=(EVAL_BATCH_SIZE , IMG_Y , IMG_X , NUMCHANNELS))

    conv1_weights = tf.Variable(tf.truncated_normal([5,5,NUMCHANNELS,32],
                                                    stddev=0.1,
                                                    seed=SEED,
                                                    dtype=tf.float32))
    conv1_biases = tf.Variable(tf.zeros([32] ,
                                        dtype=tf.float32))

    conv2_weights = tf.Variable(tf.truncated_normal(
        [5, 5, 32, 64], stddev=0.1,
        seed=SEED, dtype=tf.float32))
    conv2_biases = tf.Variable(tf.constant(0.1, shape=[64], dtype=tf.float32))

    fc1_weights = tf.Variable(
        tf.truncated_normal([IMG_Y // 4 * IMG_X // 4 * 64, 512],
                            stddev=0.1,
                            seed=SEED,
                            dtype=tf.float32))
    fc1_biases = tf.Variable(tf.constant(0.1, shape=[512], dtype=tf.float32))

    fc2_weights = tf.Variable(tf.truncated_normal([512, NUM_LABELS],
                                                  stddev=0.1,
                                                  seed=SEED,
                                                  dtype=tf.float32))
    fc2_biases = tf.Variable(tf.constant(
        0.1, shape=[NUM_LABELS], dtype=tf.float32))

    def model(data , train=False):
        conv = tf.nn.conv2d(data ,
                            conv1_weights,
                            strides=[1,1,1,1],
                            padding='SAME')
        relu = tf.nn.relu(tf.nn.bias_add(conv,conv1_biases))

        pool = tf.nn.max_pool(relu ,
                              ksize=[1,2,2,1],
                              strides=[1,2,2,1],
                              padding='SAME')

        pool_shape = pool.get_shape().as_list()

        print pool

        reshape = tf.reshape(pool,
                             [pool.shape[0], pool.shape[1] * pool_shape[2] * pool.shape[3]])

        hidden = tf.nn.relu(tf.matmul(reshape , fc1_weights) + fc1_biases)

        if train:
            hidden = tf.nn.dropout(hidden , 0.5 , seed=SEED)
        return tf.matmul(hidden , fc2_weights) + fc2_biases

    logits = model(train_data_node , True)

    print logits

    loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(
        logits , train_label_node))

    regularization = (tf.nn.l2_loss(fc1_weights) +
                      tf.nn.l2_loss(fc1_biases) +
                      tf.nn.l2_loss(fc2_weights) +
                      tf.nn.l2_loss(fc2_biases))

    loss += REGULAR_RATE * regularization

    batch = tf.Variable(0 , dtype=tf.float32)

    learning_rate = tf.train.exponential_decay(0.01 ,
                                               batch * BATCH_SIZE,
                                               train_size,
                                               0.95,
                                               staircase=True
    )

    optimizer = tf.train.MomentumOptimizer(learning_rate ,0.9).minimize(loss,global_step=batch)

    train_prediction = tf.nn.software(logits)

    eval_prediction = tf.nn.software(model(eval_data))

    print train_data_node
    print train_label_node
    print eval_data

    def eval_in_batches(data, sess):
        size = data.shape[0]
        if size < EVAL_BATCH_SIZE:
            raise ValueError("batch size for evals larger than dataset: %d" % size)
        predictions = numpy.ndarray(shape=(size, NUM_LABELS), dtype=numpy.float32)
        for begin in xrange(0, size, EVAL_BATCH_SIZE):
            end = begin + EVAL_BATCH_SIZE
            if end <= size:
                predictions[begin:end, :] = sess.run(
                    eval_prediction,
                    feed_dict={eval_data: data[begin:end, ...]})
            else:
                batch_predictions = sess.run(
                    eval_prediction,
                    feed_dict={eval_data: data[-EVAL_BATCH_SIZE:, ...]})
                predictions[begin:, :] = batch_predictions[begin - size:, :]
                return predictions
    with tf.Session() as sess:
        tf.initialize_all_variables().run()
        print ("Initialized.")

        for step in xrange(int(num_epochs * train_size) // BATCH_SIZE):
            # Compute the offset of the current minibatch in the data.
            # Note that we could use better randomization across epochs.
            offset = (step * BATCH_SIZE) % (train_size - BATCH_SIZE)
            batch_data = train_data[offset:(offset + BATCH_SIZE), ...]
            batch_labels = train_labels[offset:(offset + BATCH_SIZE)]
            # This dictionary maps the batch data (as a numpy array) to the
            # node in the graph it should be fed to.
            feed_dict = {train_data_node: batch_data,
                         train_labels_node: batch_labels}
            # Run the graph and fetch some of the nodes.
            _, l, lr, predictions = sess.run(
                [optimizer, loss, learning_rate, train_prediction],
                feed_dict=feed_dict)
            if step % EVAL_FREQUENCY == 0:
                elapsed_time = time.time() - start_time
                start_time = time.time()
                print('Step %d (epoch %.2f), %.1f ms' %
                      (step, float(step) * BATCH_SIZE / train_size,
                       1000 * elapsed_time / EVAL_FREQUENCY))
                print('Minibatch loss: %.3f, learning rate: %.6f' % (l, lr))
                print('Minibatch error: %.1f%%' % error_rate(predictions, batch_labels))
        print('Validation error: %.1f%%' % error_rate(
            eval_in_batches(validation_data, sess), validation_labels))
        sys.stdout.flush()
        # Finally print the result!
        test_error = error_rate(eval_in_batches(test_data, sess), test_labels)
        print('Test error: %.1f%%' % test_error)
        if FLAGS.self_test:
            print('test_error', test_error)
            assert test_error == 0.0, 'expected 0.0 test_error, got %.2f' % (
                test_error,)

if __name__ == '__main__':
    tf.app.run()
