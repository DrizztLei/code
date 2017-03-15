#!/usr/bin/python
# -*- coding:utf8 -*-

import os

root = '/home/elvis/DATASET/NEW_DELETE_POINT/new_delete_point/' # change here for source file directory

origin_file_name = "origin_name"
origin_directory_file_name = "origin_directory"
output_directory_file_name = "output_directory"

csv_directory_feature = "csv"
png_directory_feature = "png"
r_command = "Rscript"
r_script = "auto_builder_picture.R"
r_system_call = r_command + "\t" + r_script

filename = []


def findFile(path):
	dirList = []
	fileList = []

	files = os.listdir(path)
	for f in files:
		if os.path.isdir(path + '/' + f):
			dirList.append(f)
		if os.path.isfile(path + '/' + f):
			fileList.append(path + '/' + f)

	for dl in dirList:
		directory = str(dl)
		# print(directory)
		if directory.find("result") == -1:
			findFile(path + '/' + dl)
	for fl in fileList:
		fl = str(fl)
		if fl.endswith(".csv"):
			fl = fl.replace("\\", "/")
			filename.append(fl)

if __name__ == '__main__':
	findFile(root)

	origin_name_file = open(origin_file_name, 'w')
	origin_directory_file = open(origin_directory_file_name, 'w')
	output_directory_file = open(output_directory_file_name, 'w')

	origin_name_data = []
	origin_directory_data = []
	output_directory_data = []

	for item in filename:

		beef = os.path.split(item)
		origin_name = beef[len(beef) - 1]
		origin_name = str(origin_name)

		origin_name = origin_name.replace(".csv", "")
		origin_directory = str(beef[0])
		output_directory = origin_directory.replace(csv_directory_feature, png_directory_feature)

		origin_name_data.append(origin_name + "\n")
		origin_directory_data.append(origin_directory + "/\n")
		output_directory_data.append(output_directory + "/\n")

		# python_command = "python " + "setup.py " + origin_directory + " " + origin_name + " " + output_directory
		# os.system(python_command)
		# os.system("ls -alhs")
		# os.system(python_command)

	origin_name_file.writelines(origin_name_data)
	origin_directory_file.writelines(origin_directory_data)
	output_directory_file.writelines(output_directory_data)

	origin_name_file.close()
	origin_directory_file.close()
	output_directory_file.close()
	r_system_call = r_system_call + "\t" + origin_directory_file_name + "\t" + \
	                origin_file_name + "\t" +\
	                output_directory_file_name
	os.system(r_system_call)
