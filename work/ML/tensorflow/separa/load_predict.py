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

if len(sys.argv) == 2:
    file_name = str(sys.argv[1])
else:
    print ("parameter error.")

filename, label = get_file_name(SIZE, LABEL, LABEL_CONTROL)

flag = file_name in filename
if flag:
    index = filename.index(file_name)
    check_filename = filename[index]
    file_label = label[index]
    label = np.array([file_label])

print ("FILE NAME : %s" % file_name)

if flag:
    print ("CHECK FILE NAME : %s" % check_filename)
    print ("FILE LABEL : %s" % str(file_label))

img = cv.imread(file_name, cv.IMREAD_GRAYSCALE)

print (img.shape)
mat_show(img)
img = img[65:645, 65:645]
img = 255 - img
img = cv.resize(img, (IMAGE_SIZE, IMAGE_SIZE))

if not flag:
    print ("attention : file not in list, you should score sooner or later.")

mat_show(img)

if not flag:
    input = raw_input("file not in list, show me the score\n")
    label = np.ndarray([1])
    label[0] = int(input)
    file_label = input

img = np.reshape(img, [1, IMAGE_SIZE, IMAGE_SIZE, NUM_CHANNEL]).astype(np.float64)

print (file_name)
print (file_label)

cv.imwrite("diff.png", img[0])

data = img
SIZE = label.shape[0]

data = min_max_normalization(data)
data = np.reshape(data, [1, IMAGE_SIZE**2])

print ("lda ready")
lda = joblib.load("lda-changed.model")
print ("lda done")

matrix = np.ndarray([1, LABEL-1])

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

f = file(name=OUTFILE, mode="w+")
f.writelines(test_data)
f.close()

os.system("./lda_svm_predict.sh " + OUTFILE)