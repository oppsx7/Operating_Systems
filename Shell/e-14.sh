#! /bin/bash

if [[ ! $# -eq 1 ]]
then
echo "Invalid input"
exit 1
fi

REGEX="^[0-9]+$"

if [[ ! $1 =~ ${REGEX} ]] 
then
echo "Input an integer"
exit 2
fi

ps -e -o uid,pid,rss | sort | awk '{$1=$1};1' | grep "^0" | while
read line
do
PID=$( echo ${line} | cut -d ' ' -f 2)
RSS=$( echo ${line} | cut -d ' ' -f 3)

if [[ ${RSS} -ge ${1} ]]
then
echo "Kill ${PID}"
fi

done
