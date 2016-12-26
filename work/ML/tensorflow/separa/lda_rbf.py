from scipy import *
from scipy.linalg import norm, pinv
# from matplotlib import pyplot as plt

from numpy.linalg import norm, lstsq
# from multiprocessing import Process, Array
# from random import sample
# from ctypes import c_double
from test import *
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.externals import joblib
import tool as tool

ABS_PATH = "/home/elvis/work/ML/tensorflow/separa/"
LDA_MODEL = "lda.model"

SIZE = 828
# SIZE = 3312

BETA = 4
LABEL = 6
TRAIN_SIZE = 768
ACCELERATION_FACTOR = 256
BASE_DIVIDE = 256
# TRAIN_SIZE = 3200
BATCH_SIZE = 256
FEATURE = 4
GLOBAL_STEP = 200000000
DECAY_STEPS = 1000
EVAL_SIZE = SIZE - TRAIN_SIZE
IMAGE_SIZE = 224
PCA = 42
NUM_CHANNEL = 1
REPORT_CONTROL = 300
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 3e-3
# REGULAR = 3e-3
REGULAR = 3e-3
DROP_OUT = 8.0e-1
DECAY_RATE = 0.9998
MOMENTUM = 50e-2
SEED = random.random() * 1000
BATCH_NORMALIZATION = 1e-3


class RBF:
	def __init__(self, indim, numCenters, outdim):
		self.indim = indim
		self.outdim = outdim
		self.numCenters = numCenters
		self.centers = [np.random.uniform(-1, 1, indim) for i in xrange(numCenters)]
		self.beta = BETA
		self.W = np.random.random([numCenters, outdim])
		# self.W = random.random((self.numCenters, self.outdim))


	def _basisfunc(self, c, d):
		assert len(d) == self.indim
		return exp(-self.beta * norm(c - d) ** 2)


	def _calcAct(self, X):
		# calculate activations of RBFs
		G = zeros((X.shape[0], self.numCenters), float)
		for ci, c in enumerate(self.centers):
			for xi, x in enumerate(X):
				G[xi, ci] = self._basisfunc(c, x)
		return G


	def train(self, X, Y):
		"""
		X: matrix of dimensions n x indim
		y: column vector of dimension n x 1
		"""

		# choose random center vectors from training set
		rnd_idx = np.random.permutation(X.shape[0])[:self.numCenters]
		self.centers = [X[i, :] for i in rnd_idx]

		# print "center", self.centers
		# calculate activations of RBFs
		G = self._calcAct(X)
		# print G

		# calculate output weights (pseudoinverse)
		self.W = dot(pinv(G), Y)


	def test(self, X):
		""" X: matrix of dimensions n x indim """

		G = self._calcAct(X)
		Y = dot(G, self.W)
		return Y


if __name__ == '__main__':
	"""
	# ----- 1D Example ------------------------------------------------
	n = 100
	x = mgrid[-1:1:complex(0, n)].reshape(n, 1)
	# set y and add random noise
	y = sin(3 * (x + 0.5) ** 3 - 1)
	# y += random.normal(0, 0.1, y.shape)

	# rbf regression
	rbf = RBF(1, 10, 1)
	rbf.train(x, y)
	z = rbf.test(x)
	# plot original data
	plt.figure(figsize=(12, 8))
	plt.plot(x, y, 'k-')

	# plot learned model
	plt.plot(x, z, 'r-', linewidth=2)

	# plot rbfs
	plt.plot(rbf.centers, zeros(rbf.numCenters), 'gs')

	for c in rbf.centers:
		# RF prediction lines
		cx = arange(c - 0.7, c + 0.7, 0.01)
		cy = [rbf._basisfunc(array([cx_]), array([c])) for cx_ in cx]
		plt.plot(cx, cy, '-', color='gray', linewidth=0.2)

	plt.xlim(-1.2, 1.2)
	plt.show()
	"""

data, label = tool.parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)
data, label = tool.alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)

data = tool.min_max_normalization(data)

np.set_printoptions(threshold='nan')
single_label = np.argmax(label, 1)
SIZE = label.shape[0]
data = np.reshape(data, [SIZE, data.shape[1] ** 2])

TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
EVAL_SIZE = SIZE - TRAIN_SIZE

train_data, train_label, eval_data, eval_label = tool.random_sample(data, single_label, ACCELERATION_FACTOR, LABEL)
train_data, train_label = tool.random_shuffle(train_data, train_label)
eval_data, eval_label = tool.random_shuffle(eval_data, eval_label)

print ("lda ready")

# lda = LinearDiscriminantAnalysis(n_components=FEATURE)
# lda.fit(train_data, train_label)

# joblib.dump(lda, "lda.model")
# raw_input()
print ("lda done")
lda = joblib.load(ABS_PATH+LDA_MODEL)

fake_eval_data = np.ndarray([eval_data.shape[0], FEATURE])
fake_train_data = lda.transform(train_data)
train_data = fake_train_data

fake_eval_data = lda.transform(eval_data)
eval_data = fake_eval_data

fake_train_label = np.zeros([TRAIN_SIZE, LABEL])
fake_eval_label = np.zeros([EVAL_SIZE, LABEL])

for x in range(TRAIN_SIZE):
	fake_train_label[x, train_label[x]] = 1

for x in range(EVAL_SIZE):
	fake_eval_label[x, eval_label[x]] = 1

train_label = fake_train_label
eval_label = fake_eval_label

TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
EVAL_SIZE = SIZE - TRAIN_SIZE

# data = min_max_normalization(data)
# data = approximate_normalization(data)

print ("ALL SIZE FOR %d " % SIZE)
print ("TRAIN SIZE FOR %d " % TRAIN_SIZE)

rbf = RBF(FEATURE, 5, LABEL)
character = 'x'

final_aac = 0.0

while float(final_aac) <= 0.9:
	rbf.train(train_data, train_label)

	train_result = rbf.test(train_data)
	acc = np.sum(np.argmax(train_label, 1) == np.argmax(train_result, 1))

	print (float(acc) / train_label.shape[0])

	eval_result = rbf.test(eval_data)
	acc = np.sum(np.argmax(eval_label, 1) == np.argmax(eval_result, 1))

	print (float(acc) / eval_label.shape[0])

	final_acc = float(acc) / eval_label.shape[0]
	if final_acc > 0.85:
		final_acc = float(raw_input("Input the value : "))
