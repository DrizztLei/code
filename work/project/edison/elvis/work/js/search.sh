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
    str=""
    out="\c{\c"
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
        if [ "${str}" == "${status4}" ]
        then
#           echo "test"             
            result=""
            echo -e ",\"${status2}\":\"${result}\"\c" >> ${file}
            out=${out}",\"${status2}\":\"${result}\"\c"
        else
            if [ "${str}s" == "s" ]
            then
                result=""
                echo -e "\"${status4}\":[\n{\"${status2}\":\"${result}\"\c" >> ${file} 
                out=${out}"\"${status4}\":[\n{\"${status2}\":\"${result}\"\c"
            else
                result=""
                echo -e "}\n]," >> ${file}
                out=${out}"}\n],"
                echo -e "\"${status4}\":[\n{\"${status2}\":\"${result}\"\c" >> ${file}
                out=${out}"\"${status4}\":[\n{\"${status2}\":\"${result}\"\c"
            fi
            str=${status4}
        fi
    done
    out=${out}"}\n]}"
    echo -e "${out}" > temp
}

if [ $argc != 1 ]
then
    echo "ERROR FOR PARAMETER"
    exit -1
fi


#cd ${path}

#:<<BLOCK'
#for content in `ls ./` 
#do
#    echo ${content}
#done
#'BLOCK

hardware=$1
hardware=${hardware#*/}

#echo {"${hardware}"} > ${file}
echo -e "\c" > ${file}
echo -e "{\c" >> ${file}

filelist=`find "${path}${hardware}" -name "kernel.js" 2>err`

#if [ $argc -eq 2 ]
#then

execute ${filelist}
echo -e "}\n]}" >> ${file}

#fi
