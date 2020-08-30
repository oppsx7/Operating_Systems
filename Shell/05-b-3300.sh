#! /bin/bash


if [[ ! $# -eq 3 ]] 
then
echo "Invalid input"
exit 1
fi


cat $1 $2 | sort > $3
