"""
Simple, end-to-end, LeNet-5-like convolutional MNIST model example.
This should achieve a test error of 0.7%. Please keep this model as simple and
linear as possible, it is meant as a tutorial for simple convolutional models.
Run with --self_test on the command line to execute a short self-test.
"""

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import gzip
import os
import sys
import time

import numpy
from six.moves import urllib
from six.moves import xrange  # pylint: disable=redefined-builtin
import tensorflow as tf
import cv2 as cv
import time as te
import numpy as np

SOURCE_URL = 'http://yann.lecun.com/exdb/mnist/'
WORK_DIRECTORY = 'data'

IMAGE_SIZE = 48
NUM_CHANNELS = 3
PIXEL_DEPTH = 255
NUM_LABELS = 40
VALIDATION_SIZE = 80  # Size of the validation set.
SEED = 5254  # Set to None for random seed.
BATCH_SIZE = 320
NUM_EPOCHS = 1000
EVAL_BATCH_SIZE = 80
DROPOUT = 0.10

EVAL_FREQUENCY = 100  # Number of steps between evaluations.

REGULAR = 4.5e-6
#REGULAR = 0

INIT_LEARNING = 9.4e-6

GLOBAL_STEP = tf.Variable(0 , trainable=False)
DECAY_STEPS = 10000
DECAY_RATE = 1
ALL_STEP = 200000


tf.app.flags.DEFINE_boolean("self_test", False, "True if running a self test.")
tf.app.flags.DEFINE_boolean('use_fp16', False,
                            "Use half floats instead of full floats if True.")
FLAGS = tf.app.flags.FLAGS


def data_type():
  """Return the type of the activations, weights, and placeholder variables."""
  if FLAGS.use_fp16:
    return tf.float16
  else:
    return tf.float32


def maybe_download(filename):
  """Download the data from Yann's website, unless it's already here."""
  if not tf.gfile.Exists(WORK_DIRECTORY):
    tf.gfile.MakeDirs(WORK_DIRECTORY)
    filepath = os.path.join(WORK_DIRECTORY, filename)
  if not tf.gfile.Exists(filepath):
    filepath, _ = urllib.request.urlretrieve(SOURCE_URL + filename, filepath)
    with tf.gfile.GFile(filepath) as f:
      size = f.Size()
      print('Successfully downloaded', filename, size, 'bytes.')
  return filepath


def extract_data(filename, num_images):
  """
  Extract the images into a 4D tensor [image index, y, x, channels].
  Values are rescaled from [0, 255] down to [-0.5, 0.5].
  """
  print('Extracting', filename)
  with gzip.open(filename) as bytestream:
    bytestream.read(16)
    buf = bytestream.read(IMAGE_SIZE * IMAGE_SIZE * num_images * NUM_CHANNELS)
    data = numpy.frombuffer(buf, dtype=numpy.uint8).astype(numpy.float32)
    data = (data - (PIXEL_DEPTH / 2.0)) / PIXEL_DEPTH
    data = data.reshape(num_images, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS)
    return data


def extract_labels(filename, num_images):
  """Extract the labels into a vector of int64 label IDs."""
  print('Extracting', filename)
  with gzip.open(filename) as bytestream:
    bytestream.read(8)
    buf = bytestream.read(1 * num_images)
    labels = numpy.frombuffer(buf, dtype=numpy.uint8).astype(numpy.int64)
  return labels


def fake_data(num_images):
  """Generate a fake dataset that matches the dimensions of MNIST."""
  data = numpy.ndarray(
    shape=(num_images, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS),
    dtype=numpy.float32)
  labels = numpy.zeros(shape=(num_images,), dtype=numpy.int64)
  for image in xrange(num_images):
    label = image % 2
    data[image, :, :, 0] = label - 0.5
    labels[image] = label
  return data, labels


def error_rate(predictions, labels):
  """Return the error rate based on dense predictions and sparse labels."""
  if(predictions.shape[0] != labels.shape[0]):
    print("ERROR FOR VALUE")
    exit(-1)
  out = np.argmax(predictions , 1)

  count = 0

  for i in xrange(labels.shape[0]):
    if out[i] == labels[i]:
      count += 1
  return count / predictions.shape[0] * 100

"""
te.sleep(100)
  return 100.0 - (
    100.0 *
    np.sum(np.argmax(predictions, 1) == labels) /
    predictions.shape[0])
"""

def read(filename):
  img = cv.imread(filename)
  img = cv.resize(img , (IMAGE_SIZE , IMAGE_SIZE))
  #img = img[::,::,0:1]

  return img


def get_info(filename):
  info = np.loadtxt(filename , dtype=str , delimiter=";")
  data = info[::,0]
  label = info[::,1]
  valida_data = []
  valida_label = []
  train_data = []
  train_label = []

  length = len(data)
  for i in xrange(length):
    if (i+1) % 10 < 2 :
      """
    valida_data.append(read(info[i]))
    valida_label.append(label[i])
    """
      valida_data.append(read(data[i]))
      valida_label.append(label[i])
    else:
      """
      train_data.append(read(info[i]))
      train_label.append(info[i])
      """
      train_data.append(read(data[i]))
      train_label.append(label[i])
  return train_data , train_label , valida_data , valida_label

def main(argv=None):  # pylint: disable=unused-argument
  """
  if FLAGS.self_test:
    print('Running self-test.')
    train_data, train_labels = fake_data(256)
    validation_data, validation_labels = fake_data(EVAL_BATCH_SIZE)
    test_data, test_labels = fake_data(EVAL_BATCH_SIZE)
    num_epochs = 1
  else:
    # Get the data.
    train_data_filename = maybe_download('train-images-idx3-ubyte.gz')
    train_labels_filename = maybe_download('train-labels-idx1-ubyte.gz')
    test_data_filename = maybe_download('t10k-images-idx3-ubyte.gz')
    test_labels_filename = maybe_download('t10k-labels-idx1-ubyte.gz')

    # Extract it into numpy arrays.
    train_data = extract_data(train_data_filename, 60000)
    train_labels = extract_labels(train_labels_filename, 60000)
    test_data = extract_data(test_data_filename, 10000)
    test_labels = extract_labels(test_labels_filename, 10000)

    # Generate a validation set.
    validation_data = train_data[:VALIDATION_SIZE, ...]
    validation_labels = train_labels[:VALIDATION_SIZE]
    train_data = train_data[VALIDATION_SIZE:, ...]
    train_labels = train_labels[VALIDATION_SIZE:]
    num_epochs = NUM_EPOCHS
  """

  train_data , train_labels , test_data , test_labels = get_info("./read.csv")

  train_data = np.array(train_data , dtype=np.float32)
  train_labels = np.array(train_labels , dtype=np.int32)
  test_data = np.array(test_data , dtype=np.float32)
  test_labels = np.array(test_labels , dtype=np.int32)

  """
  validation_data = train_data[:VALIDATION_SIZE, ...]
  validation_labels = train_labels[:VALIDATION_SIZE]
  train_data = train_data[VALIDATION_SIZE:, ...]
  train_labels = train_labels[VALIDATION_SIZE:]
  """

  validation_data = test_data
  validation_labels = test_labels

  num_epochs = NUM_EPOCHS

  train_size = train_labels.shape[0]

  # This is where training samples and labels are fed to the graph.
  # These placeholder nodes will be fed a batch of training data at each
  # training step using the {feed_dict} argument to the Run() call below.

  train_data_node = tf.placeholder(
    dtype=tf.float32,
    shape=(BATCH_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS))

  train_labels_node = tf.placeholder(tf.int32, shape=(BATCH_SIZE,))

  eval_data = tf.placeholder(
    dtype=tf.float32,
    shape=(EVAL_BATCH_SIZE , IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS))

  # The variables below hold all the trainable weights. They are passed an
  # initial value which will be assigned when we call:
  # {tf.initialize_all_variables().run()}
  conv1_weights = tf.Variable(
    tf.truncated_normal([2, 2, NUM_CHANNELS, 32],  # 5x5 filter, depth 32.
                        stddev=0.1,
                        seed=SEED, dtype=tf.float32))
  conv1_biases = tf.Variable(tf.zeros([32], dtype=tf.float32))
  conv2_weights = tf.Variable(tf.truncated_normal(
    [5, 5, 32, 64], stddev=0.1,
    seed=SEED, dtype=tf.float32))
  conv2_biases = tf.Variable(tf.constant(0.1, shape=[64], dtype=tf.float32))
  fc1_weights = tf.Variable(  # fully connected, depth 512.
    tf.truncated_normal([IMAGE_SIZE // 4 * IMAGE_SIZE // 4 * 64, NUM_LABELS],
                        stddev=0.1,
                        seed=SEED,
                        dtype=tf.float32))
  fc1_biases = tf.Variable(tf.constant(0.1, shape=[NUM_LABELS], dtype=tf.float32))
  """
  fc2_weights = tf.Variable(tf.truncated_normal([512, NUM_LABELS],
                                                stddev=0.1,
                                                seed=SEED,
                                                dtype=tf.float32))
  fc2_biases = tf.Variable(tf.constant(
    0.1, shape=[NUM_LABELS], dtype=tf.float32))
  """
  # We will replicate the model structure for the training subgraph, as well
  # as the evaluation subgraphs, while sharing the trainable parameters.
  def model(data, train=False):
    """The Model definition."""
    # 2D convolution, with 'SAME' padding (i.e. the output feature map has
    # the same size as the input). Note that {strides} is a 4D array whose
    # shape matches the data layout: [image index, y, x, depth].
    conv = tf.nn.conv2d(input=data,
                        filter=conv1_weights,
                        strides=[1, 1, 1, 1],
                        padding='SAME')
    #print(conv)
    # Bias and rectified linear non-linearity.
    relu = tf.nn.relu(features=tf.nn.bias_add(value=conv, bias=conv1_biases))
    # Max pooling. The kernel size spec {ksize} also follows the layout of
    # the data. Here we have a pooling window of 2, and a stride of 2.
    pool = tf.nn.max_pool(value=relu,
                          ksize=[1, 2, 2, 1],
                          strides=[1, 2, 2, 1],
                          padding='SAME')
    conv = tf.nn.conv2d(pool,
                        conv2_weights,
                        strides=[1, 1, 1, 1],
                        padding='SAME')
    relu = tf.nn.relu(tf.nn.bias_add(conv, conv2_biases))
    pool = tf.nn.max_pool(relu,
                          ksize=[1, 2, 2, 1],
                          strides=[1, 2, 2, 1],
                          padding='SAME')
    # Reshape the feature map cuboid into a 2D matrix to feed it to the
    # fully connected layers.
    pool_shape = pool.get_shape().as_list()
    reshape = tf.reshape(
      pool,
      [pool_shape[0], pool_shape[1] * pool_shape[2] * pool_shape[3]])
    # Fully connected layer. Note that the '+' operation automatically
    # broadcasts the biases.
    # hidden = tf.nn.relu(tf.matmul(reshape, fc1_weights) + fc1_biases)
    # Add a 50% dropout during training only. Dropout also scales
    # activations such that no rescaling is needed at evaluation time.
    """
    if train:
      hidden = tf.nn.dropout(hidden, DROPOUT, seed=SEED)
    return tf.matmul(hidden, fc2_weights) + fc2_biases
    """

    hidden = reshape
    if train:
      hidden = tf.nn.dropout(hidden , DROPOUT , seed=SEED)
      return tf.matmul(hidden , fc1_weights) + fc1_biases

  # Training computation: logits + cross-entropy loss.
  logits = model(train_data_node, True)
  loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(
    logits, train_labels_node))

  # L2 regularization for the fully connected parameters.
  #regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases) +
   #               tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(fc2_biases))

  regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases))
  # Add the regularization term to the loss.

  loss += REGULAR * regularizers

  # Optimizer: set up a variable that's incremented once per batch and
  # controls the learning rate decay.
  batch = tf.Variable(0, dtype=data_type())
  # Decay once per epoch, using an exponential schedule starting at 0.01.
  learning_rate = tf.train.exponential_decay(
    learning_rate=INIT_LEARNING,                # Base learning rate.
    global_step=GLOBAL_STEP,  # Current index into the dataset.
    decay_steps=DECAY_STEPS,          # Decay step.
    decay_rate=DECAY_RATE,                # Decay rate.
    staircase=True)
  # Use simple momentum for the optimization.
  optimizer = tf.train.MomentumOptimizer(learning_rate,
                                         0.9).minimize(loss,
                                                       global_step=GLOBAL_STEP)

  # Predictions for the current training minibatch.
  train_prediction = tf.nn.softmax(logits)

  # Predictions for the test and validation, which we'll compute less often.
  eval_predictions = tf.nn.softmax(model(eval_data))

  # Small utility function to evaluate a dataset by feeding batches of data to
  # {eval_data} and pulling the results from {eval_predictions}.
  # Saves memory and enables this to run on smaller GPUs.
  def eval_in_batches(data, sess):

    """Get all predictions for a dataset by running it in small batches."""
    """"
    size = data.shape[0]
    if size < EVAL_BATCH_SIZE:
      raise ValueError("batch size for evals larger than dataset: %d" % size)
    """

    size = data.shape[0]
    predictions = numpy.ndarray(shape=(size, NUM_LABELS), dtype=numpy.int64)
    predictions = sess.run(eval_predictions , feed_dict={eval_data:data})

    """
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
    """

    return predictions

  # Create a local session to run the training.
  start_time = time.time()
  with tf.Session() as sess:
    # Run all the initializers to prepare the trainable parameters.
    tf.initialize_all_variables().run()
    print('Initialized!')
    # Loop through training steps.
    # for step in xrange(int(num_epochs * train_size) // BATCH_SIZE):
    for step in xrange(ALL_STEP):

      # Compute the offset of the current minibatch in the data.
      # Note that we could use better randomization across epochs.

      """
      offset = (step * BATCH_SIZE) % (train_size - BATCH_SIZE)
      batch_data = train_data[offset:(offset + BATCH_SIZE), ...]
      batch_labels = train_labels[offset:(offset + BATCH_SIZE)]
      # This dictionary maps the batch data (as a numpy array) to the
      # node in the graph it should be fed to.
      feed_dict = {train_data_node: batch_data,
                   train_labels_node: batch_labels}
      """

      feed_dict = {train_data_node : train_data,
                   train_labels_node : train_labels}

      # Run the graph and fetch some of the nodes.

      _, l, lr, predictions = sess.run(
        [optimizer, loss, learning_rate, train_prediction],
        feed_dict=feed_dict)

      if step % EVAL_FREQUENCY == 0:
        """
        elapsed_time = time.time() - start_time
        start_time = time.time()
        print('Step %d (epoch %.2f), %.1f ms' %
              (step, float(step) * BATCH_SIZE / train_size,
               1000 * elapsed_time / EVAL_FREQUENCY))
        """
        print(loss)
        print('Minibatch loss: %.3f, learning rate: %.6f' % (l, lr))
        print('Minibatch accurary: %.1f%%' % error_rate(predictions, train_labels))
        print('Validation accurary: %.1f%%' % error_rate(
          eval_in_batches(validation_data, sess), validation_labels))
        sys.stdout.flush()
        # Finally print the result!
    test_error = error_rate(eval_in_batches(test_data, sess), test_labels)
    print('Test error: %.1f%%' % test_error)

if __name__ == '__main__':
  tf.app.run()
