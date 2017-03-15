import cv2 as cv
from sklearn.decomposition import PCA
from sklearn import preprocessing
import matplotlib.pyplot as plt
import numpy as np
from test import *


def mat_show(img):
	window_name = "CV_IMAGE"
	cv.namedWindow(winname=window_name)
	while True:
		cv.imshow(winname=window_name, mat=img)
		character = cv.waitKey(100)
		if character == 97:  # for waiting the 'ESC' to excape
			cv.destroyWindow(window_name)
			return


def min_max_normalization(data, start=0, end=1):
	data = data.astype(np.float)
	min_max = preprocessing.MinMaxScaler(feature_range=(start, end))
	if len(data.shape) == 4:
		NUM_CHANNEL = data.shape[3]
		if NUM_CHANNEL == 1:
			data = np.reshape(data, newshape=[data.shape[0], data.shape[1], data.shape[2]])
			for x in range(data.shape[0]):
				data[x] = min_max.fit_transform(data[x])
			data = np.reshape(data, newshape=[data.shape[0], data.shape[1], data.shape[2], NUM_CHANNEL])
		else:
			for index in range(data.shape[0]):
				img = data[index]
				R = img[::, ::, 2]
				G = img[::, ::, 1]
				B = img[::, ::, 0]
				for channel in range(NUM_CHANNEL):
					R = min_max.fit_transform(R)
					G = min_max.fit_transform(G)
					B = min_max.fit_transform(B)
					img[::, ::, 2] = R
					img[::, ::, 1] = G
					img[::, ::, 0] = B
					data[index] = img

	elif len(data.shape) == 2:
		for x in range(data.shape[0]):
			value = np.reshape(data[x], [-1, 1])
			media = min_max.fit_transform(value)
			data[x] = np.reshape(media, data[x].shape)
	elif len(data.shape) == 3:
		for x in range(data.shape[0]):
			data[x] = min_max.fit_transform(data[x])
	elif len(data.shape) == 1:
		data = min_max.fit_transform(data)
	return data

img = cv.imread("./png/gauss-n100-5d-3largeCl_PCA_data_cls3.png", cv.IMREAD_GRAYSCALE)

img = img[65:645, 65:645]

img = cv.threshold(img, 100, 255, cv.THRESH_BINARY)[1]

mat_show(img_rotate(img, 90))

contour_extracter = PCA(n_components=100, whiten=True)

out = contour_extracter.fit_transform(img)

main_value = contour_extracter.explained_variance_ratio_

# print (np.sum(main_value))

out = contour_extracter.inverse_transform(out)

out = min_max_normalization(out, 0, 255)

out = np.where(out > 0, 255, 0)

out = out.astype(np.uint8)

temp = np.where(out == 0)

y_set = temp[1]
x_set = temp[0]

x = np.int(np.round(np.mean(x_set)))
y = np.int(np.round(np.mean(y_set)))

# x = np.sum(x_set) / len(x_set)
# y = np.sum(y_set) / len(y_set)

width = 400
height = 400

print (x)
print (y)

x1 = x - width / 2
x2 = x + width / 2

y1 = y - height / 2
y2 = y + width / 2

plt.scatter(x_set, y_set)

X = [x1, x2]
Y = [y1, y1]

plt.plot(X, Y)

X = [x2, x2]
Y = [y1, y2]

plt.plot(X, Y)

X = [x2, x1]
Y = [y2, y2]

plt.plot(X, Y)

X = [x1, x1]
Y = [y2, y1]

plt.plot(X, Y)

plt.plot()

plt.show()

# plt.show()

"""
cv_show = np.zeros(out.shape, dtype=np.uint8)
cv_show += 255
cv_show[x_set, y_set] = 0
mat_show(cv_show)
"""