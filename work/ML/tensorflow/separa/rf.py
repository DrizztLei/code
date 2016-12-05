from sklearn.ensemble import RandomForestClassifier
from sklearn.decomposition import PCA
import tool as tool
import numpy as np

SIZE = 828
IMAGE_SIZE = 224
NUM_CHANNEL = 1
LABEL = 6
BASE_DIVIDE = 128
ACCELERATION_FACTOR = 256
FEATURE = 42
FILENAME = "/home/elvis/work/ML/tensorflow/separa/pca_svm.txt"

util = tool.tool()

data, label = tool.parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)
data, label = tool.alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)
data = tool.min_max_normalization(data)

np.set_printoptions(threshold='nan')

label = np.argmax(label, 1)
SIZE = label.shape[0]

util.mat_show(data[-1])

data = np.reshape(data, [SIZE, data.shape[1]**2])

pca = PCA(n_components=FEATURE, whiten=True)

TRAIN_SIZE = SIZE - ACCELERATION_FACTOR
EVAL_SIZE = SIZE - TRAIN_SIZE

train_data, train_label, eval_data, eval_label = tool.random_sample(data, label, ACCELERATION_FACTOR, LABEL)

fake_data = np.ndarray([SIZE, FEATURE])
pca.fit(train_data)

for x in range(fake_data.shape[0]):
	data_T = np.reshape(data[x], [-1, 1])
	fake_data[x] = pca.transform(data_T)

fake_data = data

print ("rf ready")
train_data, train_label = tool.random_shuffle(train_data, train_label)
eval_data, eval_label = tool.random_shuffle(eval_data, eval_label)

"""
argv = int(sys.argv[1])
feature = argv
"""

clf = RandomForestClassifier(n_estimators=20)
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
raw_input()

feature = 41
pca = PCA(n_components=41, whiten=True)
pca.fit(train_data, train_label)
print ("rf done")

out = pca.predict(eval_data)
print (np.sum(out == eval_label) / float(eval_label.shape[0]))
raw_input()

matrix = np.ndarray([SIZE, feature])
for i in range(data.shape[0]):
        data_T = np.reshape(data[i], [1, -1])
        matrix[i] = pca.transform(data_T)

data_length = data.shape[0]
f = file(name=FILENAME, mode="w+")

for x in range(data_length):
	info = []
	str_label = str(label[x]) + " "
	info.append(str_label)
	sequence = 0
	for i in range(feature):
			value = float(matrix[x, i])
			sequence += 1
			segmentation = str(sequence) + ":" + str(value) + " "
			info.append(segmentation)
	info.append("\n")
	f.writelines(info)

f.close()
