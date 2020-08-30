#! /bin/bash

if [[ $# -gt 2 ]]
then
echo "Invalid input"
exit 1
fi

if [[ ! -d $1 ]]
then
echo "Not a directory"
exit 2
fi

if [[ $# -eq 1 ]]
then
find -L ${1} -type l
else
NUM=${2}
ls -ln ${1} | 
