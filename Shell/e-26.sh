#! /bin/bash

if [[ ! $# -eq 2 ]]
then
echo "Invalid input"
exit 1
fi

if [[ ! -d $2 ]]
then
echo "Not a directory"
exit 2
fi

if [[ ! $(ls -A $2 | wc -l | awk '{$1=$1};1') -eq 0 ]]
then
echo "Input an empty directory"
exit 4
fi

if [[ ! -f $1 ]]
then
echo "Input a file as a first argument"
exit 3
fi
COUNTER=1
touch ${2}/dict.txt
cat $1 | while
read line
do
NAME=$(echo ${line} | cut -d ':' -f 1 | tr '(' ' ' | tr -s ' ' | cut -d ' ' -f 1,2 )
TEXT=$(echo ${line} | cut -d ':' -f 2)
VAR=$(cat ${2}/dict.txt | grep -e "${NAME}" | wc -l | awk '{$1=$1};1')
if [[ ${VAR} -eq 0 ]]
then
echo "${NAME};${COUNTER}" >> ${2}/dict.txt
echo ${TEXT} > ${2}/${COUNTER}.txt 
COUNTER=$(($COUNTER +1)) 
else
TEMPCOUNT=$(cat ${2}/dict.txt | egrep "${NAME}" | cut -d ';' -f 2)
echo ${TEXT} >> ${2}/${TEMPCOUNT}.txt
fi
done

