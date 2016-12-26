import sys
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
LABEL_CONTROL = 4
OUTFILE = "out.txt"

if len(sys.argv) == 3:
    file_name = str(sys.argv[1])
    score = str(sys.argv[2])
    score = int(score)
else:
    print ("parameter error.")

img = cv.imread(file_name, cv.IMREAD_GRAYSCALE)

file_label = np.array(score)

print (img.shape)

img = img[85:640, 100:640]
img = 255 - img
img = cv.resize(img, (IMAGE_SIZE, IMAGE_SIZE))

print (file_name)
print (file_label)

img = np.reshape(img, [1, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL]).astype(np.float64)

data = img
SIZE = 1

data = min_max_normalization(data)
data = np.reshape(data, [1, IMAGE_SIZE ** 2])

print ("lda ready")
lda = joblib.load("lda-changed.model")
print ("lda done")

matrix = np.ndarray([1, LABEL - 1])

for i in range(data.shape[0]):
    data_T = np.reshape(data[i], [1, -1])
    matrix[i] = lda.transform(data_T)
matrix = min_max_normalization(matrix)

vector_space = matrix[0]

print (vector_space)

test_data = str(file_label) + " "
for x in range(len(vector_space)):
    test_data += str(x + 1) + ":" + str(vector_space[x]) + " "

test_data += "\n"

print (test_data)

f = file(name=OUTFILE, mode="a+")
f.writelines(test_data)
f.close()
