#!/bin/bash
argc=$#

MODEL=""
INPUT=""

while getopts "J:I:" argv
do
    case $argv in
   	 J)
	       MODEL=$OPTARG;;
         I)
               INPUT="${INPUT} ${OPTARG}";;
         ?)
               echo "Error for unknow parameters ."
               exit 1
               ;;
    esac
done

java -jar ${MODEL} ${INPUT}
