#!/bin/bash

for ((i=1 ; i<400 ; i++))
do
    python matrix.py $i
    echo $i >> info.log
    cp pca_svm.txt /home/elvis/environment/libsvm/libsvm-master/tools/
    python /home/elvis/environment/libsvm/libsvm-master/tools/grid.py /home/elvis/environment/libsvm/libsvm-master/tools/pca_svm.txt 1>>"${i}.log" 2>>"${i}.err"
done
