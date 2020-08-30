#! /bin/bash

if [[ ! $# -eq 1 ]]
then
echo "Invalid input"
exit 1
fi

if [[ ! -d $1 ]]
then
echo "Enter a directory name"
exit 2
fi

find -L ${1} -type l
