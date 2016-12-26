from scipy import *
from scipy.linalg import norm, pinv
import numpy as np

from matplotlib import pyplot as plt


class RBF:
	def __init__(self, indim, numCenters, outdim):
		self.indim = indim
		self.outdim = outdim
		self.numCenters = numCenters
		self.centers = [random.uniform(-1, 1, indim) for i in xrange(numCenters)]
		self.beta = 8
		self.W = random.random((self.numCenters, self.outdim))

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
		""" X: matrix of dimensions n x indim
			y: column vector of dimension n x 1 """

		# choose random center vectors from training set
		rnd_idx = random.permutation(X.shape[0])[:self.numCenters]
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
	n = 100
	x = mgrid[-1:1:complex(0, n)].reshape(n, 1)
	# set y and add random noise
	y = sin(3 * (x + 0.5) ** 3 - 1)
	# y += random.normal(0, 0.1, y.shape)

	# rbf regression
	rbf = RBF(1, 10, 1)
	rbf.train(x, y)
	z = rbf.test(x)

	# print (z)
	# print (y)

	out = z - y
	print (out.var())
