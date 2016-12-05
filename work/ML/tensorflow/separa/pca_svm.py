import tool as tool
import numpy as np

SIZE = 828
IMAGE_SIZE = 100
NUM_CHANNEL = 1
LABEL = 6
BASE_DIVIDE = 128
FILENAME = "/home/visualization/work/ML/tensorflow/separa/pca_svm.txt"

util = tool.tool()


data, label = tool.parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)
data, label = tool.alignment_data(data=data, label=label, LABEL=LABEL, BASE_DIVIDE=BASE_DIVIDE)
data = tool.min_max_normalization(data)

label = np.argmax(label, 1)

SIZE = data.shape[0]

data = np.reshape(data, (SIZE, IMAGE_SIZE * IMAGE_SIZE))

print ("pca ready")
feature = int(100)
pca = util.get_pca(n_components=feature)
matrix = pca.fit_transform(data)
temp = matrix[::, 0]

print ("pca done")
print (type(matrix))
print (matrix.shape)
raw_input()

out = pca.explained_variance_ratio_
print (out)
print np.sum(out)
raw_input()

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
	print ("run the step of %d" % x)

f.close()