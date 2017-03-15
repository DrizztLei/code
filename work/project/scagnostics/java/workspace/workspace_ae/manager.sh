#!/bin/bash

root="/home/elvis/DATASET/NEW_DELETE_POING/new_delete_point/"

csv_directory_feature="csv"
png_directory_feature="png"

# filename="`find ${root} -name "*.csv" | grep -v ".*result.*"`"
filename="`cat ./sub_workspace_a*`"

for item in ${filename}
do
    full_without_suffix=${item##*/}
    origin_name=${full_without_suffix%.*}
    directory_name=${item%${origin_name}*}
    directory_without_csv=${directory_name%${csv_directory_feature}*}
    direcotry_with_png=${directory_without_csv}"png/"

    directory=${directory_name}
    output_directory=${direcotry_with_png}

    # echo ${directory}
    # echo ${origin_name}
    # echo ${output_directory}

    bash "./setup.sh" ${directory} ${origin_name} ${output_directory}
done

