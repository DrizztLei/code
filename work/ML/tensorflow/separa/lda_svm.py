from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
import tool as tool
import numpy as np

SIZE = 828
IMAGE_SIZE = 224
NUM_CHANNEL = 1
LABEL = 6
BASE_DIVIDE = 128
ACCELERATION_FACTOR = 256
FEATURE = 42
FILENAME = "/home/elvis/work/ML/tensorflow/separa/lda_svm.txt"

util = tool.tool()

data, label = tool.parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)
data, label = tool.alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)
data = tool.min_max_normalization(data)

np.set_printoptions(threshold='nan')

label = np.argmax(label, 1)
SIZE = label.shape[0]
data = np.reshape(data, [SIZE, data.shape[1]**2])

TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
EVAL_SIZE = SIZE - TRAIN_SIZE

train_data, train_label, eval_data, eval_label = tool.random_sample(data, label, ACCELERATION_FACTOR, LABEL)

train_data, train_label = tool.random_shuffle(train_data, train_label)
eval_data, eval_label = tool.random_shuffle(eval_data, eval_label)

print ("lda ready")

lda = LinearDiscriminantAnalysis()
lda.fit(train_data, train_label)

print ("lda done")

out = lda.predict(eval_data)
print (np.sum(out == eval_label) / float(eval_label.shape[0]))
raw_input()

data, label = tool.random_shuffle(data, label)

matrix = np.ndarray([SIZE, LABEL-1])
for i in range(data.shape[0]):
        data_T = np.reshape(data[i], [1, -1])
        matrix[i] = lda.transform(data_T)

data_length = data.shape[0]
f = file(name=FILENAME, mode="w+")

for x in range(data_length):
    info = []
    str_label = str(label[x]) + " "
    info.append(str_label)
    sequence = 0
    for i in range(LABEL - 1):
            value = float(matrix[x, i])
            sequence += 1
            segmentation = str(sequence) + ":" + str(value) + " "
            info.append(segmentation)
    info.append("\n")
    f.writelines(info)
f.close()
