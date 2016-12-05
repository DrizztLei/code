import cv2 as cv
import numpy as np
from sklearn.decomposition import PCA
from sklearn import svm
from test import *

class tool:
	__pca = None
	__svm = None

	def __init__(self):
		print ("init")

	def get_pca(self, n_components=None, copy=True, whiten=False):
		if self.__pca is None:
			self.__pca = PCA(n_components=n_components, copy=copy, whiten=whiten)
		return self.__pca

	def pca_reduce_dimension(self, data):
		if self.__pca is None:
			self.get_pca()
		reduce_matrix = self.__pca.fit_transform(data)
		return reduce_matrix


	def mat_show(self, img, window_name="CV_IMAGE"):
		# type: (object, object) -> object
		cv.namedWindow(winname=window_name)
		while True:
			cv.imshow(winname=window_name, mat=img)
			character = cv.waitKey(100)
			if character == 97:  # for waiting the 'ESC' to excape
				break


	def random_sample(self, data, label, size_sample):
		data_shape = data.shape
		size = label.shape[0]
		kind = label.shape[1]
		stride = int(size / size_sample)
		train_data = np.ndarray(shape=[size - size_sample, data_shape[1], data_shape[2], data_shape[3]])
		train_label = np.ndarray(shape=[size - size_sample, kind], dtype=np.int64)
		eval_data = np.ndarray(shape=[size_sample, data_shape[1], data_shape[2], data_shape[3]])
		eval_label = np.ndarray(shape=[size_sample, kind], dtype=np.int64)
		count_train = count_eval = 0
		for x in xrange(size):
			if x % stride == 0:
				eval_data[count_eval] = data[x]
				eval_label[count_eval] = label[x]
				count_eval += 1
			else:
				train_data[count_train] = data[x]
				train_label[count_train] = label[x]
				count_train += 1

		if count_eval != size_sample:
			print ("ATTENTION FOR INT")
		return train_data, train_label, eval_data, eval_label

	def svm_train(self, data, label):
		clf = svm.SVC()
		print ("training")
		clf.fit(data, label)
		print ("done")
		return clf

	def svm_predict(self, clf, data):
		result = clf.predict(data)
		return result

"""
util = tool()
out = util.get_pca()
img = cv.imread("./out.png", cv.IMREAD_GRAYSCALE)
temp = util.pca_reduce_dimension(img)
print (temp)
"""


def file_write(data, filename=None):
	print (data)
"""

get_file_name()
SIZE = 828
IMAGE_SIZE = 580
NUM_CHANNEL = 1
LABEL = 6
data, label = parse_data(SIZE=SIZE, IMAGE_SIZE=IMAGE_SIZE, NUM_CHANNEL=NUM_CHANNEL, LABEL=LABEL)
data = np.reshape(data, [SIZE, IMAGE_SIZE, IMAGE_SIZE])
data_length = data.shape[0]
label = np.argmax(label, 1)

FILENAME = "/home/visualization/work/ML/tensorflow/separa/svm.txt"

f = file(FILENAME, "w+")

for x in range(data_length):
	info = []
	str_label = str(label[x]) + " "
	info.append(str_label)
	file_write(str_label)
	sequence = 0
	for i in range(IMAGE_SIZE):
		for j in range(IMAGE_SIZE):
			value = int(data[x, i, j])
			sequence += 1
			segmentation = str(sequence) + ":" + str(value) + " "
			info.append(segmentation)
	info.append("\n")
	f.writelines(info)
	print ("run the step of %d" % x)

f.close()

"""