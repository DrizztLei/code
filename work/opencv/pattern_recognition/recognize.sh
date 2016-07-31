#!/bin/bash
argc=$#
if [ ! ${argc} -eq 4 ]
then
    echo "Error : missmatch parameters"
    exit 0
fi
MODEL=""
INPUT=""
while getopts "M:I:" argv
do
    case $argv in
        M)
            MODEL=$OPTARG;;
        I)
            INPUT=$OPTARG;;
        ?)
            echo "Error for unknow parameters ."
            exit 1
            ;;
    esac
done
/home/elvis/work/opencv/pattern_recognition/recognize ${MODEL} ${INPUT}
