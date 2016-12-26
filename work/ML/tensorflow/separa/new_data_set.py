import numpy as np

PATH = "/home/elvis/DATASET/DATA/scatter_data/"
CSV_FILE = '/home/elvis/DATASET/SCORE/fk/out.csv'

info = np.loadtxt(CSV_FILE, delimiter=',', dtype=str)

print info.shape

directory = info[::, 0]
method_csv = info[::, 1]
score = info[::, 2:]

count = 0

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
            output_path = path.replace(".csv", "_CLS_" + str(y+1) + ".png")
            print (output_path)
            print (file_score)
            count += 1
            print count
