#!/bin/bash

info=`ps -ef | grep "^.*QQ.exe$" | awk '{print $2}'`
exe=`ps -ef | grep "^.*[CZc]\:.*$" | awk '{print $2}'`
out="${info} ${exe}"
if [ ! -n "${exe}" ]
then
    echo "process not running"
else
    kill -15 ${out} && echo "kill the process" && exit
fi
