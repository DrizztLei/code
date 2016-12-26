from sklearn.externals import joblib
from test import *
import numpy as np

SIZE = 828
IMAGE_SIZE = 224
NUM_CHANNEL = 1
LABEL = 6
BASE_DIVIDE = 128
ACCELERATION_FACTOR = 256
FEATURE = 5
FILENAME = "/home/elvis/work/ML/tensorflow/separa/check.txt"
NUMBER = 1
CHECK = 3

data, label = parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)

data = data[0:NUMBER]
label = label[0:NUMBER]
label = np.argmax(label, 1)
filename = get_filename()
filename = filename[0: NUMBER]

if NUMBER == 1:
    img = data[0]
    cv.imwrite("out.png", img)
    img = cv.imread("out.png", cv.IMREAD_GRAYSCALE)
    print (filename[0])
    print (label[0])
    mat_show(img)
else:
    for x in range(NUMBER):
        img = data[x]
        cv.imwrite("out.png", img)
        img = cv.imread("out.png", cv.IMREAD_GRAYSCALE)
        print (filename[x])
        print (label[x])
        mat_show(img)

data = min_max_normalization(data)

SIZE = label.shape[0]
data = np.reshape(data, [SIZE, data.shape[1]**2])

print ("lda ready")
lda = joblib.load("lda-changed.model")
print ("lda done")

matrix = np.ndarray([SIZE, LABEL-1])

for i in range(data.shape[0]):
        data_T = np.reshape(data[i], [1, -1])
        matrix[i] = lda.transform(data_T)
        print (matrix[i])
matrix = min_max_normalization(matrix)

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

os.system("./lda_svm_predict.sh " + FILENAME)
