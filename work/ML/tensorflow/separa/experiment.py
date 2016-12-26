import tool as tool
import numpy as np
from sklearn.decomposition import PCA

SIZE = 828
IMAGE_SIZE = 100
NUM_CHANNEL = 1
LABEL = 6
FILENAME = "/home/visualization/work/ML/tensorflow/separa/pca_svm.txt"

tool.get_file_name()
data, label = tool.parse_data(SIZE, IMAGE_SIZE, NUM_CHANNEL, LABEL)
label = np.argmax(label, 1)

data = np.reshape(data, [SIZE, IMAGE_SIZE * IMAGE_SIZE])

pca = PCA(n_components=100)
out = pca.fit_transform(data[1])
print (out.shape)
print (out)
