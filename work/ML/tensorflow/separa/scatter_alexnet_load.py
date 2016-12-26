from test import *
import os

MODEL = "model"

import tensorflow as tf
from tensorflow.python.platform import gfile

with tf.Session() as persisted_sess:
	print("load graph")
	with gfile.FastGFile("/tmp/load/test.pb", 'rb') as f:
		graph_def = tf.GraphDef()
		graph_def.ParseFromString(f.read())
		persisted_sess.graph.as_default()
		tf.import_graph_def(graph_def, name='')
	print("map variables")
	persisted_result = persisted_sess.graph.get_tensor_by_name("saved_result:0")
	tf.add_to_collection(tf.GraphKeys.VARIABLES, persisted_result)
	try:
		saver = tf.train.Saver(tf.all_variables())  # 'Saver' misnomer! Better: Persister!
	except:
		pass
	print("load data")
	saver.restore(persisted_sess, MODEL)  # now OK


	print(persisted_result.eval())
	print("DONE")
