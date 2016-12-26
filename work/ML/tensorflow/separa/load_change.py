import sys
import cv2 as cv
import numpy as np
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.externals import joblib

from test import *

if len(sys.argv) == 3:
    file_name = str(sys.argv[1])
    file_label = int(sys.argv[2])
    print (file_name)
    print (file_label)
else:
    print ("argument error")
    sys.exit(-1)

lda = joblib.load()

img = cv.imread(file_name, cv.IMREAD_GRAYSCALE)
mat_show(img)


