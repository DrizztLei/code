#!/bin/bash

file="device.json"
path="/home/elvis/enviroment/iot-sol/node_modules/hope-demo/"
args=$@
argc=$#

function execute()
{

    if [ $# == 0 ]
    then
        echo "ERROR FOR PARAMETER."
        exit -1
    fi

    #   purify=$1
    #   echo $purify

    for sub in $@
    do
        #       echo ${sub}
        status1=${sub%/kernel.js*}
        #       echo ${status1}
        status2=${status1##*/}
        #       echo ${status2}
        status3=${status1%/${status2}*}
        #       echo ${status3}
        status4=${status3##*/}
        #       echo ${status4}
#       echo "Get the thing for" ${status4} "and the service for" ${status2}
        echo -e "${status4}\t${status2}" >> ${file} 
    done

}

if [ $# != 1 ]
then
    echo "ERROR FOR PARAMETER"
    exit -1
fi

echo $1 > ${file}

#cd ${path}

#:<<BLOCK'
#for content in `ls ./` 
#do
#    echo ${content}
#done
#'BLOCK

out=`find "${path}${1}" -name "kernel.js" 2>err`

if [ $argc -eq 1 ]
then
    #   echo $argc
    execute ${out}
fi
