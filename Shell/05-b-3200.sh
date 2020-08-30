#! /bin/bash

if [[ ! $# -eq 1 ]] 
then
echo "Invalid input"
exit 1
fi

DIR=${1}
RESULT=$(find ${DIR} -mindepth 1 -maxdepth 1 | wc -l)
echo ${RESULT} 
