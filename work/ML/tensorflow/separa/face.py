import tensorflow as tf
import cv2 as cv
import numpy as np
import time as te
import random

from test import *

ABS_PATH = "/home/visualization/work/ML/tensorflow/separa/"

SIZE = 828
# SIZE = 3312

LABEL = 6
TRAIN_SIZE = 768
ACCELERATION_FACTOR = 256
BASE_DIVIDE = 256
# TRAIN_SIZE = 3200
BATCH_SIZE = 128 / 2
GLOBAL_STEP = 200000000
DECAY_STEPS = 100
EVAL_SIZE = SIZE - TRAIN_SIZE
# IMAGE_SIZE = 645 - 60
IMAGE_SIZE = 645 - 60
NUM_CHANNEL = 1
REPORT_CONTROL = 5
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 3.4e-3
# REGULAR = 3e-3
REGULAR = 1
DROP_OUT = 8.0e-1
DECAY_RATE = 0.9995
MOMENTUM = 50e-2
SEED = random.random() * 1000
BATCH_NORMALIZATION = 1e-3


# SEED = 295.730694719
# SEED = 935.121374578
# SEED = 149.555544719
# SEED = 266.751015428 pretty good for this data .


def cv_read(name):
	convert_name = ABS_PATH + str(name)
	img = cv.imread(filename=convert_name)
	img = (img[..., ..., 0:1])
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
	data, label = parse_data(SIZE=SIZE, IMAGE_SIZE=IMAGE_SIZE, NUM_CHANNEL=NUM_CHANNEL, LABEL=LABEL,
	                         BASE_DIVIDE=BASE_DIVIDE)
	# data = approximate_normalization(data)
	# data = min_max_normalization(data)

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

	global SIZE, TRAIN_SIZE
	data, label = process_data_label()
	label = np.argmax(label, 1)

	SIZE = label.shape[0]
	TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
	EVAL_SIZE = SIZE - TRAIN_SIZE

	data = min_max_normalization(data)
	train_data, train_label, eval_data, eval_label = random_sample(data, label, ACCELERATION_FACTOR, LABEL)

	train_data, train_label = random_shuffle(train_data, train_label)
	eval_data, eval_label = random_shuffle(eval_data, eval_label)

	train_label = np.reshape(train_label, [train_label.shape[0]])
	eval_label = np.reshape(eval_label, [eval_label.shape[0]])

	print ("ALL SIZE FOR %d " % SIZE)
	print ("TRAIN SIZE FOR %d " % TRAIN_SIZE)

	feed_eval_data = tf.placeholder(dtype=tf.float32, shape=[BATCH_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
	feed_eval_label = tf.placeholder(dtype=tf.int64, shape=(BATCH_SIZE, ))

	feed_train_data = tf.placeholder(tf.float32, [BATCH_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
	feed_train_label = tf.placeholder(tf.int64, shape=(BATCH_SIZE, ))

	convolution_weights = tf.Variable(initial_value=tf.truncated_normal(shape=[10, 10, NUM_CHANNEL, 1], seed=SEED,
	                                                                    stddev=0.1, dtype=tf.float32))

	convolution_biases = tf.Variable(initial_value=tf.zeros(shape=[1], dtype=tf.float32))

	convolution_weights2 = tf.Variable(initial_value=tf.truncated_normal(shape=[4, 4, 1, 1], seed=SEED,
	                                                                     stddev=0.1, dtype=tf.float32))

	convolution_biases2 = tf.Variable(initial_value=tf.zeros(shape=[1], dtype=tf.float32))

	convolution_weights3 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 3, 2], seed=SEED,
	                                                                     stddev=0.1, dtype=tf.float32))

	convolution_biases3 = tf.Variable(initial_value=tf.zeros(shape=[2], dtype=tf.float32))

	convolution_weights4 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 2, 1], seed=SEED,
	                                                                     stddev=0.1, dtype=tf.float32))

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
		initial_value=tf.constant(shape=[81, 36], value=1, dtype=tf.float32))

	fc1_biases = tf.Variable(initial_value=tf.constant(shape=[36], value=1, dtype=tf.float32))

	fc2_weights = tf.Variable(
		initial_value=tf.constant(shape=[36, 6], value=0.01, dtype=tf.float32))

	fc2_biases = tf.Variable(initial_value=tf.constant(shape=[6], value=0.01, dtype=tf.float32))

	fc3_weights = tf.Variable(initial_value=tf.constant(shape=[30, 6], value=0.01, dtype=tf.float32))

	fc3_biases = tf.Variable(initial_value=tf.constant(shape=[6], value=0.01, dtype=tf.float32))

	def forward(info=None, flag=False):
		info = tf.reshape(info, [-1, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])

		conv1 = tf.nn.conv2d(input=info,
		                     filter=convolution_weights,
		                     padding="VALID",
		                     strides=[1, 4, 4, 1])

		conv1_bn = batch_normalization(x=conv1, depth=conv1.get_shape()[-1], phase_train=flag)

		conv1_relu = tf.nn.relu(tf.nn.bias_add(conv1_bn, convolution_biases))

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
		                       ksize=[1, 4, 4, 1],
		                       strides=[1, 4, 4, 1],
		                       padding="SAME")

		"""

		conv3 = tf.nn.conv2d(input=pool2,
		                     strides=[1, 2, 2, 1],
		                     filter=convolution_weights3,
		                     padding='VALID')

		# conv3_bn = batch_normalization(x=conv3, depth=conv3.get_shape()[-1], phase_train=flag)

		relu3 = tf.nn.relu(tf.nn.bias_add(conv3, convolution_biases3))

		pool3 = tf.nn.max_pool(value=relu3,
		                       ksize=[1, 2, 2, 1],
		                       strides=[1, 2, 2, 1],
		                       padding='SAME')

		conv4 = tf.nn.conv2d(input=pool3,
		                     filter=convolution_weights4,
		                     padding='VALID',
		                     strides=[1, 2, 2, 1])

		relu4 = tf.nn.relu(tf.nn.bias_add(value=conv4, bias=convolution_biases4))

		pool4 = tf.nn.avg_pool(value=relu4,
		                       ksize=[1, 2, 2, 1],
		                       strides=[1, 2, 2, 1],
		                       padding='SAME')
		"""

		fc = tf.reshape(pool2, [-1, fc1_weights.get_shape().as_list()[0]])

		hidden = tf.matmul(fc, fc1_weights) + fc1_biases

		hidden_relu = tf.nn.relu(hidden)

		hidden_2 = tf.matmul(a=hidden_relu, b=fc2_weights) + fc2_biases

		if flag:
			hidden_2 = tf.nn.dropout(hidden_2, DROP_OUT, seed=SEED)

		network = hidden_2
		return network

	logits = forward(feed_train_data, True)

	loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(
		logits, feed_train_label))

	regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases) +
	                tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(fc2_biases))

	loss += REGULAR * regularizers
	train_predict = tf.nn.softmax(logits)

	eval_logits = forward(feed_eval_data, False)

	eval_loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(
		eval_logits, feed_eval_label))

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
	# optimizer = tf.train.MomentumOptimizer(learning_rate=learning_rate, momentum=MOMENTUM).minimize(loss=loss, global_step=TENSOR_GLOBAL_STEP)
	# optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(loss)
	# optimizer = tf.train.AdagradOptimizer(learning_rate=learning_rate).minimize(loss=loss)
	# optimizer = tf.train.FtrlOptimizer(learning_rate=learning_rate).minimize(loss)

	with tf.Session() as sess:
		print ("INIT.")
		print (SEED)
		init = tf.initialize_all_variables()
		sess.run(init)

		# tf.histogram_summary(tag="learning", values=learning_rate)
		# tf.histogram_summary(tag="regularizers", values=regularizers * REGULAR)
		# tf.histogram_summary(tag="loss", values=loss - REGULAR * regularizers)
		summer = tf.train.SummaryWriter(logdir="./log", graph=sess.graph)

		merge = tf.merge_all_summaries()

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

						feed_dict = {feed_eval_data: input,
						             feed_eval_label: input_label}

						_eval_predict, _eval_loss, _regularizers = sess.run([eval_predict, eval_loss, regularizers],
						                                                    feed_dict=feed_dict)

						media = (np.argmax(_eval_predict, 1))
						# array = (np.argmax(feed_dict[feed_eval_label], 1))
						array = feed_dict[feed_eval_label]

						temp = np.sum(media == array)
						accurate = (temp / float(SIZE - TRAIN_SIZE))
						print (media)
						print (array)

						print ("accurate %f " % accurate)
						print ("loss %f " % _eval_loss)
						acc_loss = _eval_loss
						_regularizers *= REGULAR
						print ("regularizers %f " % _regularizers)
					print ("------------------------------------>")
				for batch in xrange(limit):
					start = end = 0
					if batch == limit - 1:
						start = batch * BATCH_SIZE
						end = TRAIN_SIZE
						if end - start == 0:
							continue
					else:
						start = batch * BATCH_SIZE
						end = start + BATCH_SIZE

					input = train_data_reshape[start:end]
					input_label = train_label_reshape[start:end]

					feed_dict = {feed_train_data: input,
					             feed_train_label: input_label}

					_loss, _optimizer, _train_predict, _regular, _learn_rate = sess.run(
						[loss, optimizer, train_predict, regularizers, learning_rate],
						feed_dict=feed_dict)
					_adjust_regular = _regular * np.float32(REGULAR)

					media = (np.argmax(_train_predict, 1))
					# array = (np.argmax(input_label, 1))
					array = input_label

					temp = np.sum(media == array)

					if step % REPORT_CONTROL == 0:
						print ("loss %f" % _loss)
						print ("regular %f" % _adjust_regular)
						accurate = (temp / float(end - start))
						# summary = sess.run([merge], feed_dict=feed_dict)
						print ("accurate %f " % accurate)
						print ("learn_rate %f " % _learn_rate)
						# _merge = sess.run(merge, feed_dict=feed_dict)

	return


if '__main__' == __name__:
	tf.app.run()
