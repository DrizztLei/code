#!/bin/bash
# Author : Elvis Lei
# Email : elvis.linuxer@gmail.com

default=read.csv

if [ ! -d $1 ] || [ $# == 0  ];
then
    echo "Error for parameter not found or not a directory!"
    exit 1
fi

if [ $# == 1 ]
then
    out=${default}
else
    out=$2
fi

touch "${out}"

for dir in $(ls ${1})
do
	for file in $(ls ${1}/${dir})
	do
	    src="${1}/${dir}/${file};${dir##[!0-9]}"
 	    echo "${src}" >> "${out}"
	done
done
echo "PRE EXTRA OVER."
