#!/bin/bash


FILES=`cat $1`


for file in $FILES; do
    echo "File: $file"
    echo "-------------------------------------------------------------------"
    cat "$file"
    echo -e "\n\n\n"
done
