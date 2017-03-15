import joblib
from test import *


ABS_PATH = "/home/elvis/work/ML/tensorflow/separa/"

SIZE = 4743
# SIZE = 828
# SIZE = 3312

MODEL = "pca-svm-1000.model"
FEATURE = 1000

LABEL = 5
# LABEL = 6
TRAIN_SIZE = 8120
ACCELERATION_FACTOR = 2048
BASE_DIVIDE = 256
# TRAIN_SIZE = 3200
BATCH_SIZE = 128
GLOBAL_STEP = 200000000

DECAY_STEPS = 500
DECAY_RATE = 0.995

EVAL_SIZE = SIZE - TRAIN_SIZE
IMAGE_SIZE = 64
NUM_CHANNEL = 1
REPORT_CONTROL = 500
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 0.01
# REGULAR = 3e-3
REGULAR = 3e-3
DROP_OUT = 8.0e-1
MOMENTUM = 50e-2
# SEED = random.random() * 1000
SEED = 0
BATCH_NORMALIZATION = 1e-3


def main(argv=None):
	if argv is None:
		print ("ERROR FOR ARGV IS NONE")
	else:
		print (argv)

	global SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL, BASE_DIVIDE

	# data, label, fileset = parse_new_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL, BASE_DIVIDE)

	data, label, fileset = parse_new_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL, BASE_DIVIDE)

	data, label = alignment_data(data, label, LABEL, BASE_DIVIDE)

	SIZE = label.shape[0]

	data = np.reshape(data, [SIZE, -1])

	data = data.T

	data = approximate_normalization(data)

	data = data.T

	print ("pca ing .")

	filename = MODEL

	pca = joblib.load(filename)

	print (pca)

	data = pca.transform(data)

	print ("pca done .")

	print (data.shape)

	TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
	EVAL_SIZE = SIZE - TRAIN_SIZE

	data = approximate_normalization(data)

	train_data, train_label, eval_data, eval_label = random_sample(data, label, ACCELERATION_FACTOR, LABEL)

	train_data, train_label = random_shuffle(train_data, train_label)
	eval_data, eval_label = random_shuffle(eval_data, eval_label)

	train_data = train_data.astype(np.float32)
	eval_data = eval_data.astype(np.float32)

	print ("ALL SIZE FOR %d " % SIZE)
	print ("TRAIN SIZE FOR %d " % TRAIN_SIZE)

	feed_eval_data = tf.placeholder(dtype=tf.float32, shape=[None, FEATURE], name="feed_eval_data")
	feed_eval_label = tf.placeholder(dtype=tf.int64, shape=[None, LABEL], name="feed_eval_label")

	feed_train_data = tf.placeholder(dtype=tf.float32, shape=[None, FEATURE], name="feed_train_data")
	feed_train_label = tf.placeholder(dtype=tf.int64, shape=[None, LABEL], name="feed_train_label")

	fc1_weights = tf.Variable(initial_value=tf.truncated_normal(shape=[FEATURE, 40], stddev=0.1, dtype=tf.float32), name="fc1")

	fc1_biases = tf.Variable(initial_value=tf.zeros(shape=[40], dtype=tf.float32), name="fc1_bias")

	fc2_weights = tf.Variable(
		initial_value=tf.truncated_normal(shape=[40, 10], stddev=0.1, seed=SEED, dtype=tf.float32), name="fc2")

	fc2_biases = tf.Variable(initial_value=tf.zeros(shape=[10], dtype=tf.float32), name="fc2_bias")

	fc3_weights = tf.Variable(
		initial_value=tf.truncated_normal(shape=[10, LABEL], stddev=0.1, seed=SEED, dtype=tf.float32), name="fc3")

	fc3_biases = tf.Variable(initial_value=tf.zeros(shape=[LABEL], dtype=tf.float32), name="fc3_bias")

	def forward(info=None, flag=False):
		info = tf.reshape(info, [-1, FEATURE])

		fc = tf.reshape(info, [-1, fc1_weights.get_shape().as_list()[0]])

		hidden = tf.matmul(fc, fc1_weights) + fc1_biases

		# hidden_bn = batch_normalization(x=hidden, depth=hidden.get_shape()[-1], phase_train=flag)

		hidden_bn = batch_norm(hidden, flag)

		hidden_relu = tf.nn.relu(hidden_bn)

		if flag:
			hidden_relu = tf.nn.dropout(hidden_relu, keep_prob=DROP_OUT)

		hidden_2 = tf.matmul(a=hidden_relu, b=fc2_weights) + fc2_biases

		hidden_2_relu = tf.nn.relu(hidden_2)

		if flag:
			hidden_3 = tf.nn.dropout(hidden_2_relu, keep_prob=DROP_OUT)

			hidden_3 = tf.matmul(a=hidden_2_relu, b=fc3_weights) + fc3_biases

		else:
			hidden_3 = tf.matmul(a=hidden_2_relu, b=fc3_weights) + fc3_biases

		network = hidden_3

		return network

	logits = forward(feed_train_data, True)

	loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits, feed_train_label))

	regularizers = (tf.nn.l2_loss(fc1_weights) + tf.nn.l2_loss(fc1_biases) + tf.nn.l2_loss(fc2_weights) + tf.nn.l2_loss(
		fc2_biases) + tf.nn.l2_loss(fc3_weights) + tf.nn.l2_loss(fc3_biases))

	loss += REGULAR * regularizers

	train_predict = tf.nn.softmax(logits)

	eval_logits = forward(feed_eval_data, False)

	eval_loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(eval_logits, feed_eval_label))

	eval_predict = tf.nn.softmax(eval_logits)

	TENSOR_GLOBAL_STEP = tf.Variable(0, dtype=tf.int64)
	learning_rate = tf.train.exponential_decay(
		LEARNING_RATE,  # Base learning rate.
		TENSOR_GLOBAL_STEP,  # Current index into the dataset.
		DECAY_STEPS,  # Decay step.
		DECAY_RATE,  # Decay rate.
		staircase=True)

	# optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(loss=loss)
	# optimizer = tf.train.RMSPropOptimizer(learning_rate=learning_rate, decay=DECAY_RATE).minimize(loss)
	optimizer = tf.train.MomentumOptimizer(learning_rate=learning_rate, momentum=MOMENTUM).minimize(loss=loss,
	                                                                                                global_step=TENSOR_GLOBAL_STEP)
	# optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(loss)
	# optimizer = tf.train.AdagradOptimizer(learning_rate=learning_rate).minimize(loss=loss)
	# optimizer = tf.train.FtrlOptimizer(learning_rate=learning_rate).minimize(loss)

	with tf.Session() as sess:
		print ("INIT.")
		print (SEED)

		loss_summary = tf.summary.scalar("loss", loss)
		eval_loss_summary = tf.summary.scalar("eval_loss", eval_loss)
		regularizers_summary = tf.summary.scalar("regular", regularizers)

		merge = tf.summary.merge_all()

		summary_writer = tf.summary.FileWriter("./log", sess.graph)

		saver = tf.train.Saver()

		init = tf.global_variables_initializer()

		sess.run(init)

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

						input_data = eval_data[start:end]
						input_label = eval_label[start:end]

						feed_dict = {feed_eval_data: input_data, feed_eval_label: input_label}

						_eval_predict, _eval_loss, _regularizers = sess.run([eval_predict, eval_loss, regularizers],
						                                                    feed_dict=feed_dict)

						media = (np.argmax(_eval_predict, 1))
						array = (np.argmax(feed_dict[feed_eval_label], 1))

						temp = np.sum(media == array)
						accurate = float(temp) / float(end - start)
						acc_loss = _eval_loss
						_regularizers *= REGULAR

						print (media)
						print (array)

						print ("accurate %s " % str(accurate))
						print ("loss %s " % str(_eval_loss))
						print ("regularizers %s " % str(_regularizers))

						# save_path = saver.save(sess, "/tmp/model.ckpt")

					# _merge = sess.run([merge], feed_dict=feed_dict)
					# summary_writer.add_summary(_merge)

					print ("------------------------------------>")

				for batch in range(limit):

					if batch == limit - 1:
						start = batch * BATCH_SIZE
						end = TRAIN_SIZE
						if end - start == 0:
							continue
					else:
						start = batch * BATCH_SIZE
						end = start + BATCH_SIZE

					input_data = train_data[start:end]
					input_label = train_label[start:end]

					feed_dict = {feed_train_data: input_data, feed_train_label: input_label}

					_loss, _optimizer, _train_predict, _regular, _learn_rate = sess.run(
						[loss, optimizer, train_predict, regularizers, learning_rate],
						feed_dict=feed_dict)

					if step % REPORT_CONTROL == 0:
						_adjust_regular = _regular * REGULAR

						media = (np.argmax(_train_predict, 1))
						array = (np.argmax(input_label, 1))
						temp = np.sum(media == array)

						_loss -= float(_adjust_regular)

						accurate = temp / float(end - start)

						print ("loss %s" % str(_loss))
						print ("regular %s" % str(_adjust_regular))
						print ("accurate %s " % str(accurate))
						print ("learn_rate %s " % str(_learn_rate))
	return


if '__main__' == __name__:
	tf.app.run()
