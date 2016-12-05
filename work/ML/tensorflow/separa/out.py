#!/usr/bin/env python
# coding=utf-8

import cv2 as cv

img = cv.imread("/home/elvis/work/ML/tensorflow/gauss-n100-10d-5smallCl_TSNE_cls5.png")

print(img)
out = img[65:655,65:655]

print(out.shape())
