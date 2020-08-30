#! /bin/bash

REGEX="^-\?[0-9]*$"
MAX_SUM=0
COUNT=$(cat ${1} | grep ${REGEX} | wc -l | awk '{$1=$1};1')
cat ${1} | grep "${REGEX}" | while
read line
do
SUM=$(echo $line | awk '{for (i = sum = 0; i++ < length;) s += substr($0, i, 1); print s}')
if [[ ${SUM} -gt ${MAX_SUM} ]]
then
MAX_SUM=$SUM
MIN=${line}
fi

if [[ ${SUM} -eq ${MAX_SUM} ]]
then
	if [[ ${line} -lt ${MIN} ]]
	then
	MIN=${line}
	MAX_SUM=${SUM}
	fi
fi
COUNT=$(($COUNT -1))

if [[ ${COUNT} -eq 0 ]]
then
echo ${MIN}
fi
done
