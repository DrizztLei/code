#!/usr/bin/python
# -*- coding:utf8 -*-


# directory="/home/elvis/DATASET/NEW_MEASURE/Clumpy/Funnel/funnel_100_10/csv/"
# input="funnel_100_10_picture_0_rate_0.01"
# output_directory="./output/"

import sys
import os
jar="scagnostics.jar"


if __name__ == '__main__':


	args = sys.argv

	directory = args[1]
	input_name = args[2]
	output_directory = args[3]

	java_command = str("java -jar ") + jar + " " + directory + " " + input_name + " " + output_directory
	r_command = "Rscript " + "auto_builder_picture.R" + " " + directory + " " + input_name + " " + output_directory

	# print (java_command)
	print (r_command)

	# print (directory)
	# print (input)
	# print (output_directory)

	# os.system(java_command)
	# os.system(r_command)