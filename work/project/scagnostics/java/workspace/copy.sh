#!/bin/bash


for item in a b c d e f g h i j k l m n o p
do
    cp *R "./workspace_a"${item}
    cp *sh "./workspace_a"${item}
    cp *jar "./workspace_a"${item}

    rm "./workspace_a"${item}"/move.sh"
    rm "./workspace_a"${item}"/copy.sh"
done
