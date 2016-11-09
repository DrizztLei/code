#!/bin/bash

#pid=$$

#if [ -z $pid ]
#then
#    read -p "PID: " pid
#fi

#number=`ps -p ${pid:-$$} -o ppid=`

#nunmer="`ps -l | grep $$ | awk {'print $4'} | sed -n '1p'`"

#number=$2

/usr/bin/node /home/elvis/work/yun-init/server.js & 
#sleep 2

#kill -9 $number
