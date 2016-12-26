import tool as tool
from test import *
from sklearn.manifold import TSNE

from sklearn.externals import joblib
import sys

ABS_PATH = "/home/elvis/work/ML/tensorflow/separa/"

SIZE = 828
# SIZE = 3312

LABEL = 6
TRAIN_SIZE = 768
ACCELERATION_FACTOR = 256
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

LEARNING_RATE = 1e-4
# REGULAR = 3e-3
REGULAR = 3e-4
DROP_OUT = 8.0e-1
DECAY_RATE = 0.9995
MOMENTUM = 95e-2
SEED = random.random() * 1000
BATCH_NORMALIZATION = 1e-3

TRAIN_FILENAME = "/home/elvis/work/ML/tensorflow/separa/t_sne_svm_train.txt"
EVAL_FILENAME = "/home/elvis/work/ML/tensorflow/separa/t_sne_svm_eval.txt"

if len(sys.argv) == 2:
	feature = int(sys.argv[1])
else:
	feature = 100

FEATURE =feature

data, label = parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)

data, label = alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)

SIZE = data.shape[0]

data = np.reshape(data, newshape=[SIZE, -1])

label = np.argmax(label, 1)

SIZE = data.shape[0]

data = np.reshape(data, [SIZE, -1])

train_data, train_label, eval_data, eval_label = tool.random_sample(data, label, ACCELERATION_FACTOR, LABEL)

TRAIN_SIZE = train_label.shape[0]
EVAL_SIZE = eval_label.shape[0]

train_data, train_label = tool.random_shuffle(train_data, train_label)
eval_data, eval_label = tool.random_shuffle(eval_data, eval_label)

print (train_data.shape)
print (eval_data.shape)

print ("t-sne ready")

t_sne = TSNE(n_components=FEATURE, n_iter=10000, n_iter_without_progress=10)

t_sne.fit_transform(train_data)

filename = "t-sne-svm-" + str(feature) + ".model"

joblib.dump(t_sne, filename)

pca = joblib.load(filename)

print ("pca done")

train_matrix = t_sne.fit_transform(train_data)

# train_matrix = approximate_normalization(train_matrix)
data_length = TRAIN_SIZE

f = file(name=TRAIN_FILENAME, mode="w+")
for x in range(data_length):
	info = []
	str_label = str(train_label[x]) + " "
	info.append(str_label)
	sequence = 0
	for i in range(FEATURE):
		value = float(train_matrix[x, i])
		sequence += 1
		segmentation = str(sequence) + ":" + str(value) + " "
		info.append(segmentation)
	info.append("\n")
	f.writelines(info)
f.close()

eval_matrix = t_sne.fit_transform(eval_data)

for i in range(EVAL_SIZE):
	data_T = np.reshape(eval_data[i], [1, -1])
	eval_matrix[i] = pca.transform(data_T)

# eval_matrix = approximate_normalization(eval_matrix)

data_length = EVAL_SIZE

f = file(name=EVAL_FILENAME, mode="w+")
for x in range(data_length):
	info = []
	str_label = str(eval_label[x]) + " "
	info.append(str_label)
	sequence = 0
	for i in range(FEATURE):
		value = float(eval_matrix[x, i])
		sequence += 1
		segmentation = str(sequence) + ":" + str(value) + " "
		info.append(segmentation)
	info.append("\n")
	f.writelines(info)
f.close()

print ("generate file done")
