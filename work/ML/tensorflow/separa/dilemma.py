from numpy import *
from multiprocessing import Process, Array
from random import sample
from ctypes import c_double
from h5py import File


def metrics(a, b):
	return norm(a - b)


def gaussian(x, mu, sigma):
	return exp(- metrics(mu, x) ** 2 / (2 * sigma ** 2))


def multiQuadric(x, mu, sigma):
	return pow(metrics(mu, x) ** 2 + sigma ** 2, 0.5)


def invMultiQuadric(x, mu, sigma):
	return pow(metrics(mu, x) ** 2 + sigma ** 2, -0.5)


def plateSpine(x, mu):
	r = metrics(mu, x)
	return (r ** 2) * log(r)


class Rbf:
	def __init__(self, prefix='rbf', workers=4, extra_neurons=0, from_files=None):
		self.prefix = prefix
		self.workers = workers
		self.extra_neurons = extra_neurons

		# Import partial model
		if from_files is not None:
			w_handle = self.w_handle = File(from_files['w'], 'r')
			mu_handle = self.mu_handle = File(from_files['mu'], 'r')
			sigma_handle = self.sigma_handle = File(from_files['sigma'], 'r')

			self.w = w_handle['w']
			self.mu = mu_handle['mu']
			self.sigmas = sigma_handle['sigmas']

			self.neurons = self.sigmas.shape[0]

	def _calculate_error(self, y):
		self.error = mean(abs(self.os - y))
		self.relative_error = true_divide(self.error, mean(y))

	def _generate_mu(self, x):
		n = self.n
		extra_neurons = self.extra_neurons

		# TODO: Make reusable
		mu_clusters = loadtxt('clusters100.txt', delimiter='\t')

		mu_indices = sample(range(n), extra_neurons)
		mu_new = x[mu_indices, :]
		mu = vstack((mu_clusters, mu_new))

		return mu

	def _calculate_sigmas(self):
		neurons = self.neurons
		mu = self.mu

		sigmas = zeros((neurons,))
		for i in xrange(neurons):
			dists = [0 for _ in xrange(neurons)]
			for j in xrange(neurons):
				if i != j:
					dists[j] = metrics(mu[i], mu[j])
			sigmas[i] = mean(dists) * 2
		# max(dists) / sqrt(neurons * 2))
		return sigmas

	def _calculate_phi(self, x):
		C = self.workers
		neurons = self.neurons
		mu = self.mu
		sigmas = self.sigmas
		phi = self.phi = None
		n = self.n

		def heavy_lifting(c, phi):
			s = jobs[c][1] - jobs[c][0]
			for k, i in enumerate(xrange(jobs[c][0], jobs[c][1])):
				for j in xrange(neurons):
					# phi[i, j] = metrics(x[i,:], mu[j])**3)
					# phi[i, j] = plateSpine(x[i,:], mu[j]))
					# phi[i, j] = invMultiQuadric(x[i,:], mu[j], sigmas[j]))
					phi[i, j] = multiQuadric(x[i, :], mu[j], sigmas[j])
				# phi[i, j] = gaussian(x[i,:], mu[j], sigmas[j]))
				if k % 1000 == 0:
					percent = true_divide(k, s) * 100
					print c, ': {:2.2f}%'.format(percent)
			print c, ': Done'

		# distributing the work between 4 workers
		shared_array = Array(c_double, n * neurons)
		phi = frombuffer(shared_array.get_obj())
		phi = phi.reshape((n, neurons))

		jobs = []
		workers = []

		p = n / C
		m = n % C
		for c in range(C):
			jobs.append((c * p, (c + 1) * p + (m if c == C - 1 else 0)))
			worker = Process(target=heavy_lifting, args=(c, phi))
			workers.append(worker)
			worker.start()

		for worker in workers:
			worker.join()

		return phi

	def _do_algebra(self, y):
		phi = self.phi

		w = lstsq(phi, y)[0]
		os = dot(w, transpose(phi))
		return w, os
		# Saving to HDF5
		os_h5 = os_handle.create_dataset('os', data=os)

	def train(self, x, y):
		self.n = x.shape[0]

		## Initialize HDF5 caches
		prefix = self.prefix
		postfix = str(self.n) + '-' + str(self.extra_neurons) + '.hdf5'
		name_template = prefix + '-{}-' + postfix
		phi_handle = self.phi_handle = File(name_template.format('phi'), 'w')
		os_handle = self.w_handle = File(name_template.format('os'), 'w')
		w_handle = self.w_handle = File(name_template.format('w'), 'w')
		mu_handle = self.mu_handle = File(name_template.format('mu'), 'w')
		sigma_handle = self.sigma_handle = File(name_template.format('sigma'), 'w')

		## Mu generation
		mu = self.mu = self._generate_mu(x)
		self.neurons = mu.shape[0]
		print '({} neurons)'.format(self.neurons)
		# Save to HDF5
		mu_h5 = mu_handle.create_dataset('mu', data=mu)

		## Sigma calculation
		print 'Calculating Sigma...'
		sigmas = self.sigmas = self._calculate_sigmas()
		# Save to HDF5
		sigmas_h5 = sigma_handle.create_dataset('sigmas', data=sigmas)
		print 'Done'

		## Phi calculation
		print 'Calculating Phi...'
		phi = self.phi = self._calculate_phi(x)
		print 'Done'
		# Saving to HDF5
		print 'Serializing...'
		phi_h5 = phi_handle.create_dataset('phi', data=phi)
		del phi
		self.phi = phi_h5
		print 'Done'

		## Algebra
		print 'Doing final algebra...'
		w, os = self.w, _ = self._do_algebra(y)
		# Saving to HDF5
		w_h5 = w_handle.create_dataset('w', data=w)
		os_h5 = os_handle.create_dataset('os', data=os)

		## Calculate error
		self._calculate_error(y)
		print 'Done'

	def predict(self, test_data):
		mu = self.mu = self.mu.value
		sigmas = self.sigmas = self.sigmas.value
		w = self.w = self.w.value

		print 'Calculating phi for test data...'
		phi = self._calculate_phi(test_data)
		os = dot(w, transpose(phi))
		savetxt('iok3834.txt', os, delimiter='\n')
		return os

	@property
	def summary(self):
		return '\n'.join( \
			['-----------------',
			 'Training set size: {}'.format(self.n),
			 'Hidden layer size: {}'.format(self.neurons),
			 '-----------------',
			 'Absolute error   : {:02.2f}'.format(self.error),
			 'Relative error   : {:02.2f}%'.format(self.relative_error * 100)])


def predict(test_data):
	mu = File('rbf-mu-212243-2400.hdf5', 'r')['mu'].value
	sigmas = File('rbf-sigma-212243-2400.hdf5', 'r')['sigmas'].value
	w = File('rbf-w-212243-2400.hdf5', 'r')['w'].value

	n = test_data.shape[0]
	neur = mu.shape[0]

	mu = transpose(mu)
	mu.reshape((n, neur))

	phi = zeros((n, neur))
	for i in range(n):
		for j in range(neur):
			phi[i, j] = multiQuadric(test_data[i, :], mu[j], sigmas[j])

	os = dot(w, transpose(phi))
	savetxt('iok3834.txt', os, delimiter='\n')
	return os


from scipy import *
from scipy.linalg import norm, pinv
from numpy.linalg import norm, lstsq
from test import *
from sklearn.externals import joblib

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

import tool as tool

model = Rbf()
data, label = tool.parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)
data, label = tool.alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)

data = tool.min_max_normalization(data)
single_label = np.argmax(label, 1)
SIZE = label.shape[0]
data = np.reshape(data, [SIZE, data.shape[1] ** 2])

TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
EVAL_SIZE = SIZE - TRAIN_SIZE

train_data, train_label, eval_data, eval_label = tool.random_sample(data, single_label, ACCELERATION_FACTOR, LABEL)
train_data, train_label = tool.random_shuffle(train_data, train_label)
eval_data, eval_label = tool.random_shuffle(eval_data, eval_label)

print ("lda ready")

lda = joblib.load(ABS_PATH+LDA_MODEL)

print ("lda done")


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

train_label = np.argmax(train_label, 1)
eval_label = np.argmax(eval_label, 1)

TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
EVAL_SIZE = SIZE - TRAIN_SIZE

# data = min_max_normalization(data)
# data = approximate_normalization(data)

print ("ALL SIZE FOR %d " % SIZE)
print ("TRAIN SIZE FOR %d " % TRAIN_SIZE)

model.train(train_data, train_label)
