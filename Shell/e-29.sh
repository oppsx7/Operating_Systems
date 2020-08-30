#! /bin/bash

NUM_REGEX="^[0-9]*$"
N=10
ARG_COUNT=$#
BEGIN=1
touch tempFile.txt
if [[ $1 == "-n" ]]
then
	if [[ ! $2 =~ ${NUM_REGEX} ]]
	then
	echo "Invalid input"
	exit 1
	else
	N=$2
	fi
BEGIN=3
fi

for (( i=${BEGIN}; i<=${ARG_COUNT}; i++ ))
do
FILE="echo \$$i"
FILENAME=$(eval ${FILE})
NAME=$(eval ${FILE} | cut -d '.' -f 1)
cat $FILENAME | head -n $N | while
read line 
do
TIME=$(echo ${line} | cut -d ' ' -f 1,2)
DATA=$(echo ${line} | cut -d ' ' -f 3-)
echo "$TIME $NAME $DATA" >> tempFile.txt
done
done
cat tempFile.txt
rm tempFile.txt
