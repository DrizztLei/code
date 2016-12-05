#!/bin/bash

for ((i=10 ; i<200 ; i++))
do
    python matrix.py $i
    echo $i >> info.log
    cp pca_svm.txt /home/visualization/environment/libsvm/libsvm-master/tools/
    python /home/visualization/environment/libsvm/libsvm-master/tools/grid.py /home/visualization/environment/libsvm/libsvm-master/tools/pca_svm.txt 1>>"${i}.log" 2>>"${i}.err"
done
