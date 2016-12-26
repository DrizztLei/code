#!/bin/bash

for ((i=1 ; i<400 ; i++))
do
    python pca_svm.py $i
    echo $i >> info.log
    cp pca_svm_*.txt /home/elvis/environment/libsvm/libsvm-master/tools/
    python /home/elvis/environment/libsvm/libsvm-master/tools/grid.py /home/elvis/environment/libsvm/libsvm-master/tools/pca_svm_train.txt 1>>"${i}.log" 2>>"${i}.err"
done
