import numpy as np
import cv2 as cv

from test import *

out = np.loadtxt("/home/visualization/work/ML/tensorflow/separa/RESULTS_EUROVIS2015.csv", dtype=str, delimiter=',')
fileName = get_data(0)
fileName = data_trim(fileName)
classNum = get_data(3)
classNum = data_trim(classNum)

csv = []

for x in range(fileName.shape[0]):
    csv.append(combine_csv(fileName[x], classNum[x]))
data = []
for x in range(len(csv)):
    data.append([])
    vector = np.loadtxt(csv[x], delimiter=',')
