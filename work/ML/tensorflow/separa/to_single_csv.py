import numpy as np
import sys
import matplotlib.pyplot as plt
import os

filename = sys.argv[1]

DIRECTORY = "/home/elvis/DATASET/DATA/scatter_data/"

OUT_CSV_DIRECTORY = "/home/elvis/plot/csv/"
OUT_PNG_DIRECTORY = "/home/elvis/plot/png/"

info = np.loadtxt(fname = str(DIRECTORY + filename), delimiter=',')

if info.shape[1] != 3:
	print ("not 2 dimension.")
	sys.exit(-1)

x = info[..., 1:2]
y = info[..., 2:3]

output_path = filename

output_png_path = output_path

output_csv_path = output_path.replace(".png", ".csv")
output_csv_path = output_csv_path.replace("DATASET/DATA/scatter_data", "plot/csv")

output_csv_path = str(output_csv_path)
position = output_csv_path.rfind("/")

temp_csv_list = list(output_csv_path)
temp_csv_list[position] = "_"
output_csv_path = ''.join(temp_csv_list)

output_png_path = output_png_path.replace("DATASET/DATA/scatter_data", "plot/png")
output_png_path = output_png_path.replace(".csv", ".png")

temp_png_list = list(output_png_path)
temp_png_list[position] = "_"
output_png_path = ''.join(temp_png_list)

output_png_path = OUT_PNG_DIRECTORY + str(output_png_path)
output_csv_path = OUT_CSV_DIRECTORY + str(output_csv_path)

# plt.scatter(x, y)
# figure.savefig(output_path)

print ("save to csv file %s ." % output_csv_path)
print ("save to png file %s ." % output_png_path)

open_file = open(output_csv_path, 'w')

for row in range(len(x)):
	dx = float(x[row])
	dy = float(y[row])
	data = str(dx) + "," + str(dy) + "\n"
	open_file.write(data)

open_file.close()