from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.ensemble import RandomForestClassifier
import tool as tool
import numpy as np

SIZE = 828
IMAGE_SIZE = 224
NUM_CHANNEL = 1
LABEL = 6
BASE_DIVIDE = 128
ACCELERATION_FACTOR = 256
FEATURE = 42
FILENAME = "/home/elvis/work/ML/tensorflow/separa/lda_rf.txt"

util = tool.tool()

data, label = tool.parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)
data, label = tool.alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)
data = tool.min_max_normalization(data)

np.set_printoptions(threshold='nan')

label = np.argmax(label, 1)
SIZE = label.shape[0]
data = np.reshape(data, [SIZE, data.shape[1] ** 2])

TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
EVAL_SIZE = SIZE - TRAIN_SIZE

train_data, train_label, eval_data, eval_label = tool.random_sample(data, label, ACCELERATION_FACTOR, LABEL)

train_data, train_label = tool.random_shuffle(train_data, train_label)
eval_data, eval_label = tool.random_shuffle(eval_data, eval_label)

print ("lda ready")

lda = LinearDiscriminantAnalysis()
lda.fit(train_data, train_label)

print ("lda done")
fake_train_data = np.ndarray([TRAIN_SIZE, LABEL-1])
fake_eval_data = np.ndarray([EVAL_SIZE, LABEL-1])

for x in range(TRAIN_SIZE):
	data_T = np.reshape(train_data[x], [-1, 1])
	fake_train_data[x] = lda.transform(data_T)
for x in range(EVAL_SIZE):
	data_T = np.reshape(eval_data[x], [-1, 1])
	fake_eval_data[x] = lda.transform(data_T)

train_data = fake_train_data
eval_data = fake_eval_data

clf = RandomForestClassifier(n_estimators=200)
clf.fit(train_data, train_label)

print (train_data.shape)
print (eval_data.shape)
print (eval_label)

train_predict = clf.predict(train_data)
eval_predict = clf.predict(eval_data)
eval_result = np.sum(eval_predict == eval_label) / float(eval_label.shape[0])
train_result = np.sum(eval_predict == eval_label) / float(eval_label.shape[0])

print (eval_predict)
print (eval_result)
print (train_result)