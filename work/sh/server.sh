#!/bin/bash

pid=$$

if [ -z $pid ]
then
    read -p "PID: " pid
fi

number=`ps -p ${pid:-$$} -o ppid=`

/usr/bin/node ~/server.js & 

sleep 2

kill -9 $number
