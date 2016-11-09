#!/bin/bash

function printUsage()
{

    echo "1 : Philips Open"
    echo "2 : Philips Close"
    echo "3 : Switch Open"
    echo "4 : Switch Close"
    echo "5 : Computer Open"
    echo "6 : Phone "
}


while true
do
    printUsage;

    read var

    echo $var

    if [ ${var} == 1 ]
    then
        ./philipsOn.sh
    fi

    if [ ${var} == 2 ]
    then
        ./philipsOff.sh
    fi

    if [ ${var} == 3 ]
    then
        ./switchOn.sh
    fi

    if [ ${var} == 4 ]
    then
        ./switchOff.sh
    fi

    if [ ${var} == 5 ]
    then
        /usr/bin/node ./computer.js
    fi

    if [ ${var} == 6 ]
    then
        echo "Phone "
    fi

done
