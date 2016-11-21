import tensorflow as tf

import cv2 as cv
import numpy as np
import random as rd

SIZE = 400
LABEL = 40
TRAIN_SIZE = 320
BATCH_SIZE = 320
GLOBAL_STEP = 20000000
DECAY_STEPS = 10
EVAL_SIZE = SIZE - TRAIN_SIZE
IMAGE_SIZE = 64
NUM_CHANNEL = 1
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 0.01
REGULAR = 3e-2
DECAY_RATE = 95e-2
DROP_OUT = 85e-2
MOMENTUM = 7e-1
DECAY_START_STEP = tf.Variable(initial_value=0)
REPORT_CONTROL = 20
SEED = int(rd.uniform(1, 1000))

def cv_read(name):
	img = cv.imread(name)
	img = (img[..., ..., 0])
	img = cv.resize(src=img, dsize=(IMAGE_SIZE, IMAGE_SIZE))
	return img


def read(file_name):
	info = np.loadtxt(fname=file_name, dtype=str, delimiter=';')
	data = info[..., 0]
	label = info[..., 1]
	return_label = np.zeros([SIZE, LABEL], dtype=np.int64)
	return_data = []

	for i in xrange(len(data)):
		return_data.append(pretreatment(data[i]).reshape(IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL))
		return_label[i, int(label[i]) - 1] = 1
	return np.array(return_data), return_label


def pretreatment(name):
	return cv_read(name=name)


def show_img(img):
	cv.namedWindow("IMG")
	while True:
		cv.imshow("IMG", img)
		character = cv.waitKey(1000)
		if int(character) == 'a':
			break


def main(argv=None):
	if argv is None:
		print ("ERROR FOR ARGV IS NONE")
	else:
		print (argv)

	data, label = read("./read.csv")

	train_data = data
	train_label = label.astype(dtype=np.int64)

	temp_data = data.reshape([LABEL, SIZE / LABEL, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
	temp_label = label.reshape([LABEL, SIZE / LABEL, LABEL])
	start = int((SIZE / LABEL) * (TRAIN_SIZE / float(SIZE)))
	end = (SIZE / LABEL)

	eval_data = temp_data[::, start:end]
	eval_label = temp_label[::, start:end]

	eval_data = eval_data.reshape(SIZE - TRAIN_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL)
	eval_label = eval_label.reshape(SIZE - TRAIN_SIZE, LABEL)

	feed_train_data = tf.placeholder(dtype=tf.float32, shape=[None, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])

	feed_train_label = tf.placeholder(dtype=tf.float32, shape=(None, LABEL))

	feed_eval_data = tf.placeholder(dtype=tf.float32, shape=[None, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])

	feed_eval_label = tf.placeholder(dtype=tf.float32, shape=[None, LABEL])

	convolution_weights = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, NUM_CHANNEL, 50], seed=SEED,
	                                                                    stddev=0.1, dtype=tf.float32))

	convolution_biases = tf.Variable(initial_value=tf.zeros(shape=[50], dtype=tf.float32))

	convolution_weights2 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 50, 40], seed=SEED,
	                                                                     stddev=0.1, dtype=tf.float32))

	convolution_biases2 = tf.Variable(initial_value=tf.zeros(shape=[40], dtype=tf.float32))

	convolution_weights3 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 40, 30], seed=SEED,
	                                                                     stddev=0.1, dtype=tf.float32))

	convolution_biases3 = tf.Variable(initial_value=tf.zeros(shape=[30], dtype=tf.float32))

	fc1_weights = tf.Variable(
		initial_value=tf.constant(shape=[30 * (IMAGE_SIZE / 8) ** 2, 256], value=0.01, dtype=tf.float32))

	fc1_biases = tf.Variable(initial_value=tf.constant(shape=[256], value=0.01, dtype=tf.float32))

	fc2_weights = tf.Variable(
		initial_value=tf.constant(shape=[256, 40], value=0.01, dtype=tf.float32))

	fc2_biases = tf.Variable(initial_value=tf.constant(shape=[40], value=0.01, dtype=tf.float32))

	def forward(info=None, flag=False):

		info = tf.reshape(tensor=info, shape=[-1, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])

		conv = tf.nn.conv2d(input=info,
		                    filter=convolution_weights,
		                    padding="SAME",
		                    strides=[1, 1, 1, 1])

		relu = tf.nn.relu(tf.nn.bias_add(conv, convolution_biases))

		pool = tf.nn.max_pool(value=relu,
		                      ksize=[1, 2, 2, 1],
		                      strides=[1, 2, 2, 1],
		                      padding="SAME")

		conv2 = tf.nn.conv2d(input=pool,
		                     strides=[1, 1, 1, 1],
		                     padding="SAME",
		                     filter=convolution_weights2)

		relu2 = tf.nn.relu(tf.nn.bias_add(conv2, convolution_biases2))

		pool2 = tf.nn.max_pool(value=relu2,
		                       ksize=[1, 2, 2, 1],
		                       padding="SAME",
		                       strides=[1, 2, 2, 1])

		conv3 = tf.nn.conv2d(input=pool2,
		                     filter=convolution_weights3,
		                     padding='SAME',
		                     strides=[1, 1, 1, 1])

		relu3 = tf.nn.relu(tf.nn.bias_add(value=conv3, bias=convolution_biases3))

		pool3 = tf.nn.max_pool(value=relu3,
		                       ksize=[1, 2, 2, 1],
		                       strides=[1, 2, 2, 1],
		                       padding='SAME')

		reshape = tf.reshape(shape=[-1, fc1_weights.get_shape().as_list()[0]], tensor=pool3)

		hidden = tf.nn.relu(tf.matmul(a=reshape, b=fc1_weights) + fc1_biases)
		if flag:
			hidden = tf.nn.dropout(x=tf.nn.relu(tf.matmul(hidden, fc2_weights) + fc2_biases), keep_prob=DROP_OUT,
			                       seed=SEED)
		else:
			hidden = tf.nn.relu(tf.matmul(hidden, fc2_weights) + fc2_biases)
		return hidden

	logist = forward(feed_train_data, True)
	loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logist, feed_train_label))
	regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases) +
	                tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(fc2_biases))
	loss += REGULAR * regularizers
	learning_rate = tf.train.exponential_decay(learning_rate=LEARNING_RATE,
	                                           global_step=DECAY_START_STEP,
	                                           decay_rate=DECAY_RATE,
	                                           decay_steps=DECAY_STEPS)

	# optimizer = tf.train.GradientDescentOptimizer(learning_rate=LEARNING_RATE).minimize(loss=loss)
	# optimizer = tf.train.MomentumOptimizer(learning_rate=learning_rate, momentum=MOMENTUM).minimize(loss)
	optimizer = tf.train.AdadeltaOptimizer(learning_rate=learning_rate).minimize(loss=loss)
	# optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(loss=loss)
	# optimizer = tf.train.AdagradOptimizer(learning_rate=learning_rate).minimize(loss)

	"""
	optimizer = tf.train.AdamOptimizer
	optimizer = tf.train.AdagradOptimizer
	optimizer = tf.train.FtrlOptimizer
	optimizer = tf.train.GradientDescentOptimizer
	optimizer = tf.train.FtrlOptimizer
	optimizer = tf.train.RMSPropOptimizer
	optimizer = tf.train.SyncReplicasOptimizer
	optimizer = tf.train.MomentumOptimizer
	optimizer = tf.train.Optimizer
	"""

	train_predict = tf.nn.softmax(logist)
	eval_logist = forward(info=feed_eval_data)
	eval_predict = tf.nn.softmax(eval_logist)
	eval_loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(eval_logist, feed_eval_label))

	with tf.Session() as sess:

		init = tf.initialize_all_variables()
		sess.run(init)
		saver = tf.train.Saver()

		# tf.histogram_summary(tag="learning", values=learning_rate)
		# tf.histogram_summary(tag="regularizers", values=regularizers * REGULAR)
		# tf.histogram_summary(tag="loss", values=loss - REGULAR * regularizers)

		summer = tf.train.SummaryWriter(logdir="./log", graph=sess.graph)
		merge = tf.merge_all_summaries()

		# train_data_reshape = (np.reshape(a=train_data,
		# newshape=[LABEL, TRAIN_SIZE / LABEL, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL]))
		# train_lable_reshape = (np.reshape(a=train_label, newshape=[LABEL, TRAIN_SIZE / LABEL]))
		print (SEED)
		for step in xrange(GLOBAL_STEP):

			all_batch = TRAIN_SIZE // BATCH_SIZE
			rate = float(BATCH_SIZE) / TRAIN_SIZE
			unit = TRAIN_SIZE / LABEL

			if step % REPORT_CONTROL == 0:
				print ("step for %d " % step)
			for batch in xrange(TRAIN_SIZE // BATCH_SIZE):
				# start = float(batch) / all_batch * unit
				# end = start + rate * unit

				start = batch * BATCH_SIZE
				end = start + BATCH_SIZE

				# input = train_data_reshape[::, start:end, ..., ..., ...]
				# input = np.reshape(a=input, newshape=feed_train_data.get_shape())
				input = train_data[start:end, ::, ::, ::]
				# input_label = train_lable_reshape[::, start:end]
				# input_label = np.reshape(a=input_label, newshape=feed_train_label.get_shape())
				input_label = train_label[start:end, ::]
				# input = train_data[BATCH_SIZE * batch:BATCH_SIZE * batch + BATCH_SIZE, ..., ..., ...]
				# input_label = train_label[BATCH_SIZE * batch:BATCH_SIZE * batch + BATCH_SIZE]

				feed_dict = {feed_train_data: input,
				             feed_train_label: input_label}

				_optimizer, _loss, _learning_rate, _train_predict = sess.run(
					[optimizer, loss, learning_rate, train_predict], feed_dict)

				_regularizers = sess.run(regularizers, feed_dict)

				print ("loss : %f" % _loss)

				array = feed_dict[feed_train_label]
				array = array.astype(dtype=np.int64)
				array = np.argmax(array, 1)

				media = np.argmax(a=_train_predict, axis=1).astype(dtype=np.int64)

				temp = np.sum(media == array) / float(SIZE - TRAIN_SIZE)
				print ('accuracy : %f' % temp)
				print ("loss : %f" % _loss)
				print ("regularizers : %f" % (_regularizers * REGULAR))

			if step % REPORT_CONTROL == 0:
				print ("EVAL")
				input = eval_data
				input_label = eval_label

				feed_dict = {feed_eval_data: input, feed_eval_label: input_label}

				_eval_loss, _eval_predict = sess.run([eval_loss, eval_predict], feed_dict)

				array = feed_dict[feed_eval_label]
				array = array.astype(dtype=np.int64)
				array = np.argmax(array, 1)

				media = np.argmax(a=_eval_predict, axis=1).astype(dtype=np.int64)

				temp = np.sum(media == array) / float(SIZE - TRAIN_SIZE)
				print ('accuracy : %f' % temp)
				print ("loss : %f" % _eval_loss)
				print (np.argmax(_eval_predict, 1))
				if _eval_loss < 0.1:
					saver.save(sess=sess, save_path="/home/elvis/work/ML/tensorflow/graph.ckpt")

		return


if '__main__' == __name__:
	tf.app.run()
