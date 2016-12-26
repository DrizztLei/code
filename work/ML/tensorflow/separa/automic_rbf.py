import numpy as np
import os

scrip = "/home/elvis/work/ML/tensorflow/separa/auto-rbf.sh"

mse_start = 0.01
mse_end = 1.00
mse_number = 100
mse = np.linspace(mse_start, mse_end, mse_number)

gw_start = 0.01
gw_end = 0.1
gw_number = 10
gw = np.linspace(gw_start, gw_end, gw_number)

count = 0
for x in mse:
	for y in gw:
		print (count)
		count += 1
		os.system("/bin/bash " + scrip + "\t" + str(x) + "\t" + str(y))

"""
for x in mse:
	print ('step for %f ' % x)
	os.system("/bin/bash " + scrip + "\t" + str(x) + "\t" + str(0))
"""