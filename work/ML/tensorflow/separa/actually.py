import xlrd
import numpy as np
import os

data = xlrd.open_workbook('/home/elvis/DATASET/SCORE/fk/lda.xlsx')
DIRECTORY = "/home/elvis/DATASET/DATA/scatter_data/"

table = data.sheets()[0]
nrows = table.nrows
ncols = table.ncols

for i in xrange(0, nrows):
    rowValues = table.row_values(i)
    count = 0
    count_label = 0
    fileName = ""
    csv = ""
    label = []
    for item in rowValues:
        count += 1
        item = str(item)
        length = len(item)
        if length != 0:
            if count == 1:
                fileName = item
            elif count == 2:
                csv = item
            else:
                f_item = float(item)
                mark = int(f_item)
                label.append(mark)
    path = DIRECTORY + fileName + "/" + csv

    label = np.array(label)
    print path
    print label
    length = len(label)
    for index in range(1, length+1):
        os.system("python scatter_to_picture.py " + str(path) + " " + str(index) + " " + str(label[index - 1]))