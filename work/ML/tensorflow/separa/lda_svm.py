from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.externals import joblib
import tool as tool
import numpy as np
from test import *

ABS_PATH = "/home/elvis/work/ML/tensorflow/separa/"

SIZE = 4746
# SIZE = 3312

LABEL = 5
TRAIN_SIZE = 768
ACCELERATION_FACTOR = 2048
BASE_DIVIDE = 256
# TRAIN_SIZE = 3200
BATCH_SIZE = 8192
GLOBAL_STEP = 200000000
DECAY_STEPS = 10000
EVAL_SIZE = SIZE - TRAIN_SIZE
# IMAGE_SIZE = 645 - 60
IMAGE_SIZE = 64
NUM_CHANNEL = 1
REPORT_CONTROL = 500
TRAIN_SLICE = (int(SIZE / LABEL * round((float(TRAIN_SIZE) / SIZE), 1)))

LEARNING_RATE = 0.01
# REGULAR = 3e-3
REGULAR = 3e-3
DROP_OUT = 8.0e-1
DECAY_RATE = 0.9995
MOMENTUM = 95e-2
SEED = random.random() * 1000
BATCH_NORMALIZATION = 1e-3

TRAIN_FILENAME = "/home/elvis/work/ML/tensorflow/separa/lda_svm_train.txt"
EVAL_FILENAME = "/home/elvis/work/ML/tensorflow/separa/lda_svm_eval.txt"

util = tool.tool()

# data, label = tool.parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)
data, label = parse_new_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)

print (label[0])
mat_show(data[0])

print (label[1])
mat_show(data[1])

print (label[-1])
mat_show(data[-1])

data, label, fileset = alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)

SIZE = label.shape[0]

TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
EVAL_SIZE = SIZE - TRAIN_SIZE

data = np.reshape(data, [SIZE, -1])

data = tool.min_max_normalization(data)

label = np.argmax(label, 1)


for x in range(len(data[0])):
    value = data[0, x]
    if value != 0:
        print value

print ("shape for ")
print (data.shape)
print (label.shape)

train_data, train_label, eval_data, eval_label = tool.random_sample(data, label, ACCELERATION_FACTOR, LABEL)

train_data, train_label = tool.random_shuffle(train_data, train_label)
eval_data, eval_label = tool.random_shuffle(eval_data, eval_label)

print ("lda ready")

lda = LinearDiscriminantAnalysis()
lda.fit(train_data, train_label)

joblib.dump(lda, "lda-svm.model")

lda = joblib.load("lda-svm.model")

print ("lda done")

eval_out = lda.predict(eval_data)
print (eval_out)
print (eval_label)
print (np.sum(eval_out == eval_label) / float(eval_label.shape[0]))

train_out = lda.predict(train_data)
print (np.sum(train_out == train_label) / float(train_label.shape[0]))

# data, label = tool.random_shuffle(data, label)
train_matrix = np.ndarray([TRAIN_SIZE, LABEL-1])
for i in range(TRAIN_SIZE):
        data_T = np.reshape(train_data[i], [1, -1])
        train_matrix[i] = lda.transform(data_T)

train_matrix = tool.min_max_normalization(train_matrix)
data_length = TRAIN_SIZE

f = file(name=TRAIN_FILENAME, mode="w+")
for x in range(data_length):
    info = []
    str_label = str(train_label[x]) + " "
    info.append(str_label)
    sequence = 0
    for i in range(LABEL - 1):
            value = float(train_matrix[x, i])
            sequence += 1
            segmentation = str(sequence) + ":" + str(value) + " "
            info.append(segmentation)
    info.append("\n")
    f.writelines(info)
f.close()

eval_matrix = np.ndarray([EVAL_SIZE, LABEL-1])

for i in range(EVAL_SIZE):
        data_T = np.reshape(eval_data[i], [1, -1])
        eval_matrix[i] = lda.transform(data_T)

eval_matrix = tool.min_max_normalization(eval_matrix)
data_length = EVAL_SIZE

f = file(name=EVAL_FILENAME, mode="w+")
for x in range(data_length):
    info = []
    str_label = str(eval_label[x]) + " "
    info.append(str_label)
    sequence = 0
    for i in range(LABEL - 1):
            value = float(eval_matrix[x, i])
            sequence += 1
            segmentation = str(sequence) + ":" + str(value) + " "
            info.append(segmentation)
    info.append("\n")
    f.writelines(info)
f.close()

print ("generate file done")
