import cv2 as cv
import numpy as np
import os as os
import math
import random
from sklearn import preprocessing
from sklearn.decomposition import PCA
import tensorflow as tf

DIR_PATH = "/home/elvis/work/ML/tensorflow/separa/"
FIG_PATH = DIR_PATH + "EUROVIS_figures/"
NEW_PATH = DIR_PATH + "EUROVIS_new/"
PNG_PATH = DIR_PATH + "png/"
CSV_FILE = "/home/elvis/work/ML/tensorflow/separa/data.csv"

global FILE
global TRAIN_DATA
global TRAIN_LABEL


def data_cluster(img):
	print ("clustering")
	shape = img.shape
	for x in shape[0]:
		for y in shape[1]:
			print ("cluster")


def data_aix_mean(img):
	img = np.sum(img, 1)
	img /= 3
	return img

def random_sample(data, label, size_sample, LABEL):
	data_shape = data.shape
	size = label.shape[0]
	kind = LABEL
	stride = np.round(size / float(size_sample))
	if len(label.shape) > 1:
		list_shape = list(data_shape[1:])
		train_shape = [size - size_sample] + list_shape
		eval_shape = [size_sample] + list_shape
		train_data = np.ndarray(shape=train_shape)
		train_label = np.ndarray(shape=[size - size_sample, kind], dtype=np.int64)
		eval_data = np.ndarray(shape=eval_shape)
		eval_label = np.ndarray(shape=[size_sample, kind], dtype=np.int64)
	else:
		list_shape = list(data_shape[1:])
		train_shape = [size - size_sample] + list_shape
		eval_shape = [size_sample] + list_shape
		train_data = np.ndarray(shape=train_shape)
		train_label = np.ndarray(shape=[size - size_sample], dtype=np.int64)
		eval_data = np.ndarray(shape=eval_shape)
		eval_label = np.ndarray(shape=[size_sample], dtype=np.int64)

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

	print ("value for train : %d" % count_train)
	print ("value for eval : %d" % count_eval)

	if count_eval != size_sample:
		print ("ATTENTION FOR INT")
	return train_data, train_label, eval_data, eval_label


def get_figure():
	info = os.listdir(FIG_PATH)
	return info


def get_csv():
	info = os.listdir(NEW_PATH)
	return info


def read_csv(filename):
	info = np.loadtxt(filename, dtype=str, delimiter=",")
	return info


def show_csv_info():
	info = get_csv()
	for x in xrange(len(info)):
		data_list = read_csv(NEW_PATH + info[x])
		print (data_list.shape)


def mat_show(img):
	window_name = "CV_IMAGE"
	cv.namedWindow(winname=window_name)
	while True:
		cv.imshow(winname=window_name, mat=img)
		character = cv.waitKey(100)
		if character == 97:  # for waiting the 'ESC' to excape
			cv.destroyWindow(window_name)
			return


def image_show(filename):
	img = cv.imread(filename)
	window_name = "CV_IMAGE"
	cv.namedWindow(winname=window_name)
	while True:
		cv.imshow(winname=window_name, mat=img)
		character = cv.waitKey(100)
		if character == 97:
			cv.destroyWindow(window_name)
			break


def real_csv():
	info = np.loadtxt(fname=CSV_FILE, dtype=str, delimiter=",")


def random_shuffle(DATA, LABEL):
	length = DATA.shape[0]

	for x in range(0, length):
		choice = int(random.random() * length)
		temp_data = np.array(DATA[x])
		DATA[x] = DATA[choice]
		DATA[choice] = temp_data
		temp_label = np.array(LABEL[x])
		LABEL[x] = LABEL[choice]
		LABEL[choice] = temp_label

	return DATA, LABEL


def view_class(index, RATE=830):
	info = read_csv(CSV_FILE)
	SELECT = index
	LABEL = (info[0][SELECT])

	NUM = info.shape[0]
	SELECT_NUM = (NUM // RATE)
	INFO = info[::SELECT_NUM,SELECT]
	INFO = INFO[1::]

	if type(INFO[0]) == str:
		INFO = INFO.astype(dtype=np.int64)

	RETURN_VALUE = ""
	RETURN_VALUE += str(LABEL)
	RETURN_VALUE += str(INFO)
	RETURN_VALUE = RETURN_VALUE.replace('[', ' ')
	RETURN_VALUE = RETURN_VALUE.replace(']', ' ')
	temp = list(RETURN_VALUE)

	return RETURN_VALUE


def compare():
	A = view_class(4)
	B = view_class(5)
	count = 0

	A = A.replace(' ', '')
	B = B.replace(' ', '')

	A = list(A)
	B = list(B)
	A = A[6:]
	B = B[6:]

	for x in xrange(len(A)):
		if A[x] == B[x]:
			count += 1

	print ("result for %f" % (float(count)/ len(A)))


def class_1():
	temp = (view_class(0))
	out = temp.split(' ')
	a = np.array(out)
	if a[len(a)-1] == '':
		a = a[1:len(a)-1]
	return a


def data_trim(info):
	info_shape = info.shape
	info = info[0:info_shape[0] - 1]
	return info


def get_data(index=0, RATE=830):
	temp = (view_class(index, RATE))
	out = temp.split(' ')
	a = np.array(out)
	if a[len(a)-1] == '':
		a = a[1:len(a)-1]
	for x in xrange(len(a)):
		a[x] = str(a[x]).replace('\'', "")
		a[x] = str(a[x]).replace('\n', "")
	return a


def get_label(index=0, RATE=830):
	info = read_csv(CSV_FILE)
	return info[0, index]


def show_class():
	print (get_label(3))
	print (get_data(3)[0:5])
	print (get_label(0))
	print (get_data(0)[0:5])


def sum_check():
	data = get_data(3)
	arg = data.argmax()
	filename = get_data(0)
	print (filename[arg-8:arg+3])
	print (data[arg-8:arg+3])
	# print (data[arg])
	# print (get_data(0)[arg])


def combine(file_name, class_num, file_type=".png"):
	name = ""
	file_name = str(file_name)
	try:
		position = file_name.index(".csv")
		name = file_name[0:position] + "_cls" + class_num + file_type
	except:
		name = ""
	return name


def combine_csv(file_name, class_num, file_type=".csv"):
	name = ""
	file_name = str(file_name)
	try:
		position = file_name.index(".csv")
		name = file_name[0:position] + "_cls" + class_num + file_type
	except:
		name = ""
	return name


def get_file_name(SIZE, LABEL, LABEL_CONTROL):
		filename = get_data(0)
		filenum = get_data(3)
		label = get_data(LABEL_CONTROL)
		file_set = []
		for x in range(len(filename)):
				file_name = combine(filename[x], filenum[x])
				if file_name != "":
						file_set.append(PNG_PATH+file_name)
		return file_set, label

# The method is to alignment the data to the same value % 128 = 0


def find_element(img, start=0, end=256):
	for x in range(start, end):
		if x in img:
			print (x)


def alignment_data(data, label, LABEL, BASE_DIVIDE):
	print ("ALIGNMENT CALLED")
	number = data.shape[0]
	print (number)
	if len(label.shape) > 1:
		label = np.argmax(label, 1)
		statistic_of_label = np.zeros([LABEL])
		statistic_of_data = []

	for x in xrange(LABEL):
		statistic_of_data.append([])

	for x in xrange(number):
		statistic_of_label[label[x]] += 1
		statistic_of_data[label[x]].append(data[x])

	print ("STATISTIC OF LABEL")
	print (statistic_of_label)
	max_value = np.max(statistic_of_label)
	size_of_new_data = (max_value // BASE_DIVIDE + 1 ) * BASE_DIVIDE
	print ("ALIGNMENT DATA %d " % size_of_new_data)

	new_label = np.zeros([size_of_new_data * LABEL, LABEL])

	for x in range(0, LABEL):
		new_label[x * size_of_new_data:x * size_of_new_data + size_of_new_data, x] = 1
		if len(data.shape) == 4:
			data_shape = [int(size_of_new_data * LABEL), data.shape[1], data.shape[2], data.shape[3]]
		else:
			data_shape = [int(size_of_new_data * LABEL), data.shape[1]]

	print ("SHAPE FOR : ")
	print (data_shape)

	new_data = np.ndarray(shape=data_shape)

	for x in range(0, LABEL):
		temp = statistic_of_data[x][::]
		start = x * size_of_new_data
		length_of_data = len(statistic_of_data[x])
		end = start + length_of_data
		new_data[start:end] = temp
		# issue here
		length = end
		range_of_data = len(statistic_of_data[x])
		size = size_of_new_data - (end - start)
		for y in range(0, int(size)):
			seed = int(random.random() * range_of_data)
			new_data[length + y] = statistic_of_data[x][seed]
	return new_data, new_label


def z_score_normalization(x):
	mu = np.mean(x)
	sigma = np.var(x)
	x = (x - mu) / sigma
	return x


def approximate_normalization(data):
	shape = data.shape
	if len(shape) == 4:
		size = shape[0]
		height = shape[1]
		width = shape[2]
		approximate_normalization_data = np.ndarray([size, height, width, shape[-1]])

		for s in range(size):
			# R = data[s, ::, ::, 2]
			# G = data[s, ::, ::, 1]
			# out = R * (2.0 / 255) + G * (-1.0 / 255) - 1
			# approximate_normalization_data[s] = np.reshape(a=out, newshape=[height, width, 1])
			approximate_normalization_data[s] = z_score_normalization(data[s])
		return approximate_normalization_data
	elif len(shape) == 3:
		"""
		height = shape[0]
		width = shape[1]
		approximate_normalization_data = np.ndarray([height, width, 1])
		R = data[::, ::, 2]
		G = data[::, ::, 1]
		out = R * (11.0 / 55) + G * (-21.0 / 55) + 50
		# approximate_normalization_data = np.reshape(a=out, newshape=[height, width, 1])
		"""
		approximate_normalization_data = z_score_normalization(data)
		return approximate_normalization_data
	elif len(shape) == 2:
		size = data.shape[0]
		for x in range(size):
			data[x] = z_score_normalization(data[x])
		return data
		print ("ERROR FRO PROCESS DATA")


def find_element(img, start=0, end=256):
	for x in range(start, end):
		if x in img:
			print (x)


def min_max_normalization(data, start=0, end=1):
	min_max = preprocessing.MinMaxScaler(feature_range=(start, end))
	if len(data.shape) == 4:
		NUM_CHANNEL = data.shape[3]
		data = np.reshape(data, newshape=[data.shape[0], data.shape[1], data.shape[2]])
		for x in range(data.shape[0]):
			data[x] = min_max.fit_transform(data[x])
		data = np.reshape(data, newshape=[data.shape[0], data.shape[1], data.shape[2], NUM_CHANNEL])
	else:
		for x in range(data.shape[0]):
			data[x] = min_max.fit_transform(data[x])
	return data


def parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL, BASE_DIVIDE=128, pca=-1, LABEL_CONTROL=4):

	filename, label = get_file_name(SIZE, LABEL, LABEL_CONTROL)
	TRAIN_DATA = np.ndarray([SIZE, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
	TRAIN_LABEL = np.zeros([SIZE, LABEL])
	if pca == -1:
		for x in range(SIZE):
			if NUM_CHANNEL == 1:
				img = cv.imread(filename[x], cv.IMREAD_GRAYSCALE)
			else:
				img = cv.imread(filename[x])
			img = img[65:645, 65:645]
			img = 255 - img
			img = cv.resize(img, (IMAGE_SIZE, IMAGE_SIZE))
			img = np.reshape(img, [IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL])
			TRAIN_DATA[x] = img
			TRAIN_LABEL[x, label[x]] = 1
	else:
		matrix = np.ndarray([SIZE, IMAGE_SIZE**2])
		for x in range(SIZE):
			img = cv.imread(filename[x], cv.IMREAD_GRAYSCALE)
			img = img[65:645, 65:645]
			img = 255 - img
			img = cv.resize(img, (IMAGE_SIZE, IMAGE_SIZE))
			img = np.reshape(img, [IMAGE_SIZE ** 2])
			matrix[x] = img
			TRAIN_LABEL[x, label[x]] = 1
		print ("pca begin")
		tool = PCA(n_components=pca, whiten=True)
		tool.fit(matrix)
		print ("pca done")
		matrix, RETURN_TRAIN_LABEL = alignment_data(matrix, TRAIN_LABEL, LABEL, BASE_DIVIDE)
		size = RETURN_TRAIN_LABEL.shape[0]
		RETURN_TRAIN_DATA = np.ndarray([size, pca])
		for x in range(size):
			data_T = np.reshape(matrix[x], [1, -1])
			RETURN_TRAIN_DATA[x] = tool.transform(data_T)
		return RETURN_TRAIN_DATA, RETURN_TRAIN_LABEL
	return TRAIN_DATA, TRAIN_LABEL


def normalization(data):
	data = approximate_normalization(data)
	return data


def img_show(img):
	cv.namedWindow("IMG")
	while True:
		cv.imshow("IMG", img)
		character = cv.waitKey(100)
		if int(character) == 'a': break


def img_clean(img):
	return_matrix = np.zeros([img.shape[0], img.shape[1], 1])
	for x in xrange(img.shape[0]):
		for y in xrange(img.shape[1]):
			if img[x,y,0] + img[x,y,1] == 0:
				return_matrix[x,y,0] = -1
			elif img[x,y,0] + img[x,y,1] == 255:
				return_matrix[x,y,0] = 1
	return return_matrix


def img_rotate(img, angle):
	height = img.shape[0]
	width = img.shape[1]
	if angle % 180 == 0:
		scale = 1
	elif angle % 90 == 0:
		scale = float(max(height, width)) / min(height,width)
	else:
		scale = math.sqrt(pow(height,2) + pow(width,2))/min(height,width)

	rotateMat = cv.getRotationMatrix2D((width/2, height/2), angle, scale)
	rotageImg = cv.warpAffine(img, rotateMat, (width, height))
	return rotageImg


if __name__ == '__main__':
	tf.app.run()
