#! /bin/bash

if [[ ! $# -eq 2 ]]
then
echo "Invalid input"
exit 1
fi

if [[ ! -d $1 ]]
then
echo "Input a directory"
exit 2
fi

REGEX="vmlinuz-[0-9]*\.[0-9]*\.[0-9]*-[a-z0-9A-Z]*"
echo $(find ${1} -maxdepth 1 -type f | tr ' ' '\n' | grep ${REGEX} | grep ${2} | sort -n | tail -n 1)
