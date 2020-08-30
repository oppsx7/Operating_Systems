#! /bin/bash

if [[ ! $# -eq 2 ]] 
then
echo "Invalid input"
exit 1
fi

if [[ ! -f ${1} ]] 
then 
echo "Enter a file name as a first argument"
exit 2
fi

RESULT=$(cat ${1} | grep "${2}" | wc -l)

if [[ ${RESULT} -eq 0 ]]
then
echo "not found"
else
echo "contains"
fi

