import xlrd
import numpy as np
import os

filename = "/home/elvis/DATASET/DATA/scatter_data/info"

info_list = np.loadtxt(filename, dtype=str)

for path_file in info_list:
	os.system("python to_single_csv.py " + path_file)