# import xlrd
import numpy as np
import os

PATH = "/home/elvis/DATASET/DATA/scatter_data/"
CSV_FILE = '/home/elvis/DATASET/SCORE/fk/fk.csv'

"""
data = xlrd.open_workbook(
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
"""

info = np.loadtxt(CSV_FILE, delimiter=',', dtype=str)

print info.shape

directory = info[::, 0]
method_csv = info[::, 1]
score = info[::, 2:]

for x in range(score.shape[0]):
    for y in range(len(score[x])):
        value = score[x, y]
        if len(value) == 0:
            continue
        else:
            file_directory = directory[x]
            file_method = method_csv[x]
            file_score = score[x, y]
            path = PATH + file_directory + "/" + file_method
            # output_path = path.replace(".csv", "_CLS_" + str(y+1) + ".csv")
            print (path)
            # print (output_path)
            print (y + 1)
            print (file_score)
            index = y + 1
            os.system("python to_picture.py " + path + " " + str(index) + " " + str(file_score))
