#! /bin/bash

if [[ $# -gt 2 ]]
then
echo "Invalid input"
exit 1
fi

if [[ ! -d $1 ]]
then
echo "Input a directory"
exit 2
fi

SYMLINK_COUNT=$(find -L ${1} -type l | wc -l | awk '{$1=$1};1')
SYMLINK=$(find ${1} -type l)
COUNTER=${SYMLINK_COUNT}
find -L ${1} -type l | while 
read line
do
SYMLINK=$(echo ${SYMLINK} | tr ' ' '\n' | grep -v "text1cp")
if [[ ${COUNTER} -eq 1 ]]
then
	if [[ $# -eq 2 ]]
	then 
	echo ${SYMLINK} | tr ' ' '\n'  > ${2}
	echo ${SYMLINK_COUNT} >> ${2}
	else 
	echo ${SYMLINK} | tr ' ' '\n'
	echo ${SYMLINK_COUNT}
	fi
fi
COUNTER=$((${COUNTER} -1)) 
done
