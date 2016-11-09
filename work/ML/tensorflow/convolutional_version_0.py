from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import gzip
import os
import sys

from six.moves import urllib
from six.moves import xrange
import tensorflow as tf
import cv2 as cv
import time as te
import numpy as np

WORK_DIRECTORY = 'data'

IMAGE_SIZE = 92
NUM_CHANNELS = 1
PIXEL_DEPTH = 255
NUM_LABELS = 40
VALIDATION_SIZE = 80  # Size of the validation set.
SEED = None  # Set to None for random seed.
BATCH_SIZE = 1000
NUM_EPOCHS = 300
EVAL_BATCH_SIZE = 80
DROPOUT = 0.25
SIZE = 400

EVAL_FREQUENCY = 100  # Number of steps between evaluations.

REGULAR = 3e-5
INIT_LEARNING = 1e-6

GLOBAL_STEP = tf.Variable(NUM_EPOCHS)
DECAY_STEPS = 1000
DECAY_RATE = 99e-2
ALL_STEP = 2000

def error_rate(predictions, labels):

  if(predictions.shape[0] != labels.shape[0]):

    print(predictions.shape[0])
    print(labels.shape[0])

    exit(-1)

  out = np.argmax(predictions, 1)

  count = 0

  for i in xrange(labels.shape[0]):
    if out[i] == labels[i]:
      count += 1
  return (1 - count / predictions.shape[0]) * 100


def read(filename):
  img = cv.imread(filename)
  img = cv.resize(img, (IMAGE_SIZE, IMAGE_SIZE))
  img = img[::, ::, 0]

  return img


def get_info(filename):
  info = np.loadtxt(filename, dtype=str, delimiter=";")
  data = info[::,0]
  label = info[::,1]
  valida_data = []
  valida_label = []
  train_data = []
  train_label = []

  length = len(data)

  for i in xrange(length):
    if (i+1) % 10 < 2:
      valida_data.append(read(data[i]))
      valida_label.append(label[i])
    else:
      train_data.append(read(data[i]))
      train_label.append(label[i])

  return train_data, train_label, valida_data, valida_label


def main(argv=None):

  train_data, train_labels, test_data, test_labels = get_info("./read.csv")

  train_data = np.array(train_data, dtype=np.float32).reshape((SIZE - VALIDATION_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS))
  train_labels = np.array(train_labels, dtype=np.int64)
  test_data = np.array(test_data, dtype=np.float32).reshape((VALIDATION_SIZE , IMAGE_SIZE , IMAGE_SIZE, NUM_CHANNELS))
  test_labels = np.array(test_labels, dtype=np.int64)

  train_labels = train_labels - 1
  test_labels = test_labels - 1

  validation_data = test_data
  validation_labels = test_labels

  num_epochs = NUM_EPOCHS

  train_size = train_labels.shape[0]

  train_data_node = tf.placeholder(
    dtype=tf.float32,
    shape=(BATCH_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS))

  train_labels_node = tf.placeholder(tf.int64, shape=(BATCH_SIZE,))

  eval_data = tf.placeholder(
    dtype=tf.float32,
    shape=(EVAL_BATCH_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS))

  all_data = tf.placeholder(
    dtype=tf.float32,
    shape=[SIZE - VALIDATION_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNELS])


  conv1_weights = tf.Variable(
  tf.truncated_normal([16, 16, NUM_CHANNELS, 32],  # 4x4filter, depth 32.
  stddev=0.1,
  seed=SEED, dtype=tf.float32), name='conv1_weights')

  conv1_biases = tf.Variable(tf.zeros([32], dtype=tf.float32), name="conv1_weights")

  conv2_weights = tf.Variable(tf.truncated_normal(
    [16, 16, 32, 64], stddev=0.1,
    seed=SEED, dtype=tf.float32))
  conv2_biases = tf.Variable(tf.constant(0.1, shape=[64], dtype=tf.float32), name="conv2_weights")

  fc1_weights = tf.Variable(
  tf.truncated_normal([IMAGE_SIZE // 4 * IMAGE_SIZE // 4 * 64, 512],
                        stddev=0.1,
                        seed=SEED,
                        dtype=tf.float32),name="fc1_weights")
  fc1_biases = tf.Variable(tf.constant(0.1, shape=[512], dtype=tf.float32) , name="fc1_biases")

  fc2_weights = tf.Variable(tf.truncated_normal([512, NUM_LABELS],
                                                stddev=0.1,
                                                seed=SEED,
                                                dtype=tf.float32) , name="fc2_weights")
  fc2_biases = tf.Variable(tf.constant(
      0.1, shape=[NUM_LABELS], dtype=tf.float32) , name="fc2_biases")

  def model(data, train=False):
    conv = tf.nn.conv2d(input=data,
                        filter=conv1_weights,
                        strides=[1, 1, 1, 1],
                        padding='SAME',name="CONV1")

    relu = tf.nn.relu(features=tf.nn.bias_add(value=conv, bias=conv1_biases) , name="RELU1")
    pool = tf.nn.max_pool(value=relu,
                          ksize=[1, 2, 2, 1],
                          strides=[1, 2, 2, 1],
                          padding='SAME' , name="POOL1")
    conv = tf.nn.conv2d(pool,
                        conv2_weights,
                        strides=[1, 1, 1, 1],
                        padding='SAME' , name="CONV2")

    relu = tf.nn.relu(tf.nn.bias_add(conv, conv2_biases) , name="RELU2")
    pool = tf.nn.max_pool(relu,
                          ksize=[1, 2, 2, 1],
                          strides=[1, 2, 2, 1],
                          padding='SAME' , name="POOL2")

    pool_shape = pool.get_shape().as_list()
    reshape = tf.reshape(
      pool,
      [pool_shape[0], pool_shape[1] * pool_shape[2] * pool_shape[3]] , name="RESHAPE")

    hidden = tf.nn.relu(tf.matmul(reshape , fc1_weights) + fc1_biases , name="HIDDEN1")

    if train:
      hidden = tf.nn.dropout(hidden , DROPOUT , seed=SEED , name="DROPOUT")
    return tf.matmul(hidden , fc2_weights) + fc2_biases

  logits = model(train_data_node, True)
  loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(logits, train_labels_node) , name="LOSS")

  regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases) + tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(fc2_biases))

  loss += REGULAR * regularizers

  tf.histogram_summary("LOSS" , loss)
  tf.histogram_summary("REGULAR" , regularizers)

  learning_rate = tf.train.exponential_decay(
    learning_rate=INIT_LEARNING,                # Base learning rate.
    global_step=GLOBAL_STEP,  # Current index into the dataset.
    decay_steps=DECAY_STEPS,          # Decay step.
    decay_rate=DECAY_RATE,                # Decay rate.
    staircase=True)
  # Use simple momentum for the optimization.

  """
  optimizer = tf.train.MomentumOptimizer(learning_rate,
                                         0.9).minimize(loss , global_step = GLOBAL_STEP)

  """

  optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate , name="optimizer").minimize(loss=loss , global_step=GLOBAL_STEP)

  tf.histogram_summary("LEARNING" , learning_rate)


  #optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(loss , global_step=100)

  # Predictions for the current training minibatch.
  train_prediction = tf.nn.softmax(logits)

  # Predictions for the test and validation, which we'll compute less often.

  eval_predictions = tf.nn.softmax(model(eval_data))

  all_predictions = tf.nn.softmax(model(all_data))
  #tf.histogram_summary("ALL PREDICTIONS" , all_predictions)

  # Small utility function to evaluate a dataset by feeding batches of data to
  # {eval_data} and pulling the results from {eval_predictions}.
  # Saves memory and enables this to run on smaller GPUs.

  def eval_in_batches(data, sess , flag=1):
    predictions = None
    if int(flag) == 1:
      size = data.shape[0]
      predictions = np.ndarray(shape=(size, NUM_LABELS), dtype=np.int64)
      predictions = sess.run(eval_predictions , feed_dict={eval_data:data})
    elif int(flag) == 2:
      size = data.shape[0]
      predictions = np.ndarray(shape=[SIZE , NUM_LABELS] , dtype=np.int64)
      predictions = sess.run(all_predictions , feed_dict={all_data:data})
    return predictions

  start_time = te.time()

  with tf.Session() as sess:
    tf.initialize_all_variables().run()
    summary_writer = tf.train.SummaryWriter('./log' , graph = sess.graph)
    merge = tf.merge_all_summaries()

    for step in xrange(NUM_EPOCHS):
      for batch in xrange(train_data.shape[0] // BATCH_SIZE):

        begin = batch * BATCH_SIZE
        end = begin + BATCH_SIZE

        if end > SIZE - VALIDATION_SIZE:
          continue

        batch_data = train_data[begin:end , ...]
        batch_labels = train_labels[begin:end , ...]

        feed_dict = {train_data_node: batch_data,
                   train_labels_node: batch_labels}

        out , _, l, lr, predictions = sess.run(
          fetches=[merge ,optimizer, loss, learning_rate, train_prediction],
          feed_dict=feed_dict)

      if step % 10 == 0 :
        summary_writer.add_summary(out , step)

      if step % EVAL_FREQUENCY == 0:
        train_error = error_rate(eval_in_batches(train_data[0:SIZE - VALIDATION_SIZE,...] , sess , 2) , train_labels[0:SIZE - VALIDATION_SIZE,...])
        test_error = error_rate(eval_in_batches(test_data, sess), test_labels)

        print('loss for %s' % l)
        print('learing rate for %s ' % lr)
        print('Train error: %.1f%%' % train_error)
        print('Test error: %.1f%%' % test_error)

if __name__ == '__main__':
  tf.app.run()
