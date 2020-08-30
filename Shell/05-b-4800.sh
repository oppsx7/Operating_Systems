#! /bin/bash

if [[ ! $# -eq 2 ]]
then
echo "Invalid input"
exit 1
fi
if [[ ! -f $1 ]] 
then
echo "Not a file"
exit 2
fi

if [[ ! -d $2 ]]
then
echo "Not a directory"
exit 3
fi

find -f $2 | 
while read line
do
echo "FILE: ${line}"
echo "INPUT FILE: ${1}"
echo "CMP: $(cmp ${1} ${line})"
if [[ $(cmp -s ${1} ${line} | wc -l | awk '{$1=$1};1') -eq 0 ]]
then
echo "no problem"
fi
done
