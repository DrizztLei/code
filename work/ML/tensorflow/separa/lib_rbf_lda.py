import pyradbas as pyrb
from test import *
import tool as tool
from sklearn.externals import joblib
import sys

ABS_PATH = "/home/elvis/work/ML/tensorflow/separa/"
LDA_MODEL = "lda.model"

SIZE = 828
# SIZE = 3312

LABEL = 6
TRAIN_SIZE = 768
ACCELERATION_FACTOR = 256
BASE_DIVIDE = 256
# TRAIN_SIZE = 3200
BATCH_SIZE = 128
FEATURE = 5
GLOBAL_STEP = 200000000
DECAY_STEPS = 1000
EVAL_SIZE = SIZE - TRAIN_SIZE
IMAGE_SIZE = 224
PCA = 42
NUM_CHANNEL = 1
REPORT_CONTROL = 300
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 3e-5
# REGULAR = 3e-3
REGULAR = 3e-3
DROP_OUT = 4.0e-1
DECAY_RATE = 0.9999
MOMENTUM = 99e-2
SEED = random.random() * 1000
BATCH_NORMALIZATION = 1e-3

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

lda = joblib.load(ABS_PATH + LDA_MODEL)

print ("lda done")

fake_eval_data = np.ndarray([eval_data.shape[0], FEATURE])

fake_train_data = lda.transform(train_data)
train_data = fake_train_data

fake_eval_data = lda.transform(eval_data)
eval_data = fake_eval_data

fake_train_label = np.zeros([TRAIN_SIZE, LABEL])
fake_eval_label = np.zeros([EVAL_SIZE, LABEL])

"""
for x in range(TRAIN_SIZE):
	fake_train_label[x, train_label[x]] = 1
for x in range(EVAL_SIZE):
	fake_eval_label[x, eval_label[x]] = 1
"""

# train_label = fake_train_label
# eval_label = fake_eval_label


if len(sys.argv) >= 3:
	arg1 = float(sys.argv[1])
	arg2 = float(sys.argv[2])
else:
	arg1 = 0.1
	arg2 = 1

TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
EVAL_SIZE = SIZE - TRAIN_SIZE

train_label = np.reshape(train_label, [TRAIN_SIZE, 1])
eval_label = np.reshape(eval_label, [EVAL_SIZE, 1])

print ("training ")
rbf = pyrb.train_ols(train_data, train_label, mse=arg1, gw=arg2, verbose=True)
# rbf = pyrb.train_exact(train_data, train_label, 0.4)
print ("train done")

train_result = rbf.sim(train_data)
train_result = np.reshape(train_result, [-1, 1])
x = np.sum(train_result == train_label)

train_acc = np.sum(train_result == train_label) / float(TRAIN_SIZE)

eval_result = rbf.sim(eval_data)
eval_result = np.reshape(eval_result, [-1, 1])

eval_acc = np.sum(eval_result == eval_label) / float(EVAL_SIZE)

out_train = train_result - train_label
out_predict = eval_result - eval_label

print (out_train.shape)
print (out_train.shape)

print (np.sum((out_train**2)) / len(out_train))
print (np.sum((out_predict**2)) / len(out_predict))