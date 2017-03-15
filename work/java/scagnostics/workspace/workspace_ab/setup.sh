#!/bin/bash

# directory="/home/elvis/DATASET/NEW_MEASURE/Clumpy/Funnel/funnel_100_10/csv/"
# input="funnel_100_10_picture_0_rate_0.01"
# output_directory="./output/"

jar="scagnostics.jar"

directory=$1
input=$2
output_directory=$3

# sudo java -jar ${jar} ${directory} ${input} ${output_directory}
sudo Rscript auto_builder_picture.R ${directory} ${input} ${output_directory}
