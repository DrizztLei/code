from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
import tool as tool
import numpy as np
from sklearn.externals import joblib

SIZE = 828
IMAGE_SIZE = 224
NUM_CHANNEL = 1
LABEL = 6
BASE_DIVIDE = 128
ACCELERATION_FACTOR = 256
FEATURE = 5
FILENAME = "/home/elvis/work/ML/tensorflow/separa/check.txt"

util = tool.tool()

data, label = tool.parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)
data = tool.min_max_normalization(data)

label = np.argmax(label, 1)
SIZE = label.shape[0]
data = np.reshape(data, [SIZE, data.shape[1]**2])

print ("lda ready")
lda = joblib.load("lda-changed.model")
print ("lda done")

matrix = np.ndarray([SIZE, LABEL-1])

for i in range(data.shape[0]):
        data_T = np.reshape(data[i], [1, -1])
        matrix[i] = lda.transform(data_T)

matrix = tool.min_max_normalization(matrix)

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
