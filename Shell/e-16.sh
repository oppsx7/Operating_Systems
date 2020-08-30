#! /bin/bash

if [[ ! $# -eq 3 ]]
then
echo "Invalid input"
exit 1
fi

NIZ1=$(cat ${1} | grep "${2}=" | cut -d '=' -f 2)
NIZ2=$(cat ${1} | grep "${3}=" | cut -d '=' -f 2)
COUNT=$(echo ${NIZ1} | tr ' ' '\n' | wc -l)
echo ${COUNT}
VAR=${NIZ2}
echo ${NIZ1} | tr ' ' '\n' | while 
read line
do
NIZ2=$(echo ${NIZ2} | tr ' ' '\n' | grep -v "${line}")
 
if [[ ${COUNT} -eq 1 ]]
then
echo "VAR: ${VAR}"
echo $(echo ${NIZ2} | tr '\n' ' ')
cat ${1} | sed "s/${VAR}/$(echo ${NIZ2} | tr '\n' ' ')/" > ${1}
fi

COUNT=$((COUNT-1))

done

