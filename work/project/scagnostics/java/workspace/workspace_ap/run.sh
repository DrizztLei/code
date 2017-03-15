#!/bin/bash


for item in a b c d e f g h i j k l m n o p
do
    cd "./workspace_a"${item}
    ./manager.sh 1>run_info 2>run_err &
    cd ..
done
