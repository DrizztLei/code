import tensorflow as tf

import cv2 as cv
import numpy as np
import time as te

SIZE = 400
LABEL = 40
TRAIN_SIZE = 320
BATCH_SIZE = 320
GLOBAL_STEP = 200000
DECAY_STEPS = 10
EVAL_SIZE = SIZE - TRAIN_SIZE
IMAGE_SIZE = 40
NUM_CHANNEL = 1
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 4.1e-1
REGULAR = 1.2e-2
DECAY_RATE = 85e-2
SEED = 5686
DECAY_RATE = 85e-2
DROP_OUT = 5e-1


def cv_read(name):
	img = cv.imread(name)
	img = (img[..., ..., 0])
	img = cv.resize(src=img, dsize=(IMAGE_SIZE, IMAGE_SIZE))
	return img


def read(file_name):
	info = np.loadtxt(fname=file_name, dtype=str, delimiter=';')
	data = info[..., 0]
	label = info[..., 1]
	return_data = []

	for i in xrange(len(data)):
		return_data.append(pretreatment(data[i]).reshape(IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL))
	return np.array(return_data), np.array(label)


def pretreatment(name):
	return cv_read(name=name)


def main(argv=None):
	if argv is None:
		print ("ERROR FOR ARGV IS NONE")
	else:
		print (argv)

	data, label = read("./read.csv")

	train_data = (np.reshape(a=np.reshape(a=data,
	                                      newshape=[LABEL, SIZE / LABEL, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
	[..., 0:TRAIN_SLICE, ..., ..., ...],
	                         newshape=[TRAIN_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL]))

	train_label = (np.reshape(a=(np.reshape(a=label,
	                                        newshape=[LABEL, SIZE / LABEL])
	                             [..., 0:TRAIN_SLICE]),
	                          newshape=[TRAIN_SIZE]))

	train_label = train_label.astype(dtype=np.int64)
	train_label -= 1

	eval_data = (np.reshape(a=np.reshape(a=data, newshape=[LABEL, SIZE / LABEL, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
	[..., TRAIN_SLICE::, ..., ..., ...],
	                        newshape=[EVAL_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL]))

	eval_label = (np.reshape(a=np.reshape(a=label, newshape=[LABEL, SIZE / LABEL])[..., TRAIN_SLICE::],
	                         newshape=[EVAL_SIZE]))

	eval_label = eval_label.astype(dtype=np.int64)
	eval_label -= 1

	feed_train_data = tf.placeholder(dtype=tf.float32, shape=[BATCH_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])

	feed_train_label = tf.placeholder(dtype=tf.int64, shape=(BATCH_SIZE,))

	feed_eval_data = tf.placeholder(dtype=tf.float32, shape=[SIZE - TRAIN_SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])

	feed_eval_label = tf.placeholder(dtype=tf.int64, shape={SIZE - TRAIN_SIZE})

	convolution_weights = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, NUM_CHANNEL, 40], seed=SEED,
	                                                                    stddev=0.1, dtype=tf.float32))

	convolution_biases = tf.Variable(initial_value=tf.zeros(shape=[40], dtype=tf.float32))

	convolution_weights2 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 40, 30], seed=SEED,
	                                                                     stddev=0.1, dtype=tf.float32))

	convolution_biases2 = tf.Variable(initial_value=tf.zeros(shape=[30], dtype=tf.float32))

	convolution_weights3 = tf.Variable(initial_value=tf.truncated_normal(shape=[2, 2, 30, 20], seed=SEED,
	                                                                     stddev=0.1, dtype=tf.float32))

	convolution_biases3 = tf.Variable(initial_value=tf.zeros(shape=[20], dtype=tf.float32))

	fc1_weights = tf.Variable(
		initial_value=tf.constant(shape=[20 * (IMAGE_SIZE / 8) ** 2, 256], value=0.001, dtype=tf.float32))

	fc1_biases = tf.Variable(initial_value=tf.constant(shape=[256], value=0.001, dtype=tf.float32))

	fc2_weights = tf.Variable(
		initial_value=tf.constant(shape=[256, 40], value=0.001, dtype=tf.float32))

	fc2_biases = tf.Variable(initial_value=tf.constant(shape=[40], value=0.001, dtype=tf.float32))

	def forward(info=None, flag=False):
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

		pool_shape = pool3.get_shape().as_list()

		reshape = tf.reshape(shape=[pool_shape[0], pool_shape[1] * pool_shape[2] * pool_shape[3]], tensor=pool3)

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
	                tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(fc2_biases))

	loss += REGULAR * regularizers

	# op = tf.Print(loss, [loss], message='loss : ')

	learning_rate = tf.train.exponential_decay(learning_rate=LEARNING_RATE,
	                                           global_step=GLOBAL_STEP,
	                                           decay_rate=DECAY_RATE,
	                                           decay_steps=DECAY_STEPS)
	"""
	optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate,
	                                              name="Gradient_Descent_Optimzer").minimize(loss=loss)

	"""

	optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(loss=loss)

	train_predict = tf.nn.softmax(logits=logist, name="Softmax")

	# eval_predict = tf.nn.softmax(forward(feed_eval_data, False))

	start_time = te.time()

	with tf.Session() as sess:
		print ("INIT.")
		tf.initialize_all_variables().run()

		tf.histogram_summary(tag="learning", values=learning_rate)
		tf.histogram_summary(tag="regularizers", values=regularizers * REGULAR)
		tf.histogram_summary(tag="loss", values=loss - REGULAR * regularizers)

		summer = tf.train.SummaryWriter(logdir="./log", graph=sess.graph)
		merge = tf.merge_all_summaries()

		train_data_reshape = (np.reshape(a=train_data,
		                                 newshape=[LABEL, TRAIN_SIZE / LABEL, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL]))
		train_lable_reshape = (np.reshape(a=train_label, newshape=[LABEL, TRAIN_SIZE / LABEL]))

		for step in xrange(GLOBAL_STEP):

			all_batch = TRAIN_SIZE // BATCH_SIZE
			rate = float(BATCH_SIZE) / TRAIN_SIZE
			unit = TRAIN_SIZE / LABEL

			for batch in xrange(TRAIN_SIZE // BATCH_SIZE):
				start = float(batch) / all_batch * unit
				end = start + rate * unit

				input = train_data_reshape[::, start:end, ..., ..., ...]
				input = np.reshape(a=input, newshape=feed_train_data.get_shape())

				input = train_data[BATCH_SIZE * batch:BATCH_SIZE * batch + BATCH_SIZE, ..., ..., ...]

				input_label = train_lable_reshape[::, start:end]
				input_label = np.reshape(a=input_label, newshape=feed_train_label.get_shape())

				input_label = train_label[BATCH_SIZE * batch:BATCH_SIZE * batch + BATCH_SIZE]

				feed_dict = {feed_train_data: input,
				             feed_train_label: input_label}

				_merge, _optimizer, _loss, _learning_rate, _train_predict = sess.run(
					fetches=[merge, optimizer, loss, learning_rate, train_predict],
					feed_dict=feed_dict)

				# print ('---------------------------------->')

				array = feed_dict[feed_train_label]
				array = array.astype(dtype=np.int64)
				media = np.argmax(a=_train_predict, axis=1).astype(dtype=np.int64)
				temp = np.sum(media == array) / float(BATCH_SIZE)

				# print (array)
				print (media)

				print ('accuracy : %.3f' % temp )
				print ('loss : %.4f' % _loss)

				"""
				if isinstance(object=_optimizer,class_or_type_or_tuple=np.float32):
					print ('optimizer : %.4f' % _optimizer)
				"""

				# print ('learning rate : %f' % _learning_rate)
				# print ('----------------------------------<')

			if step % 5 == 0:
				summer.add_summary(summary=_merge, global_step=step)

			if step % DECAY_STEPS == 0:
				print ("TIME FOR %.1f " % (float(te.time()) - float(start_time)))
				print ("STEP FOR %d " % (step))
				start_time = te.time()
	return


if '__main__' == __name__:
	tf.app.run()
