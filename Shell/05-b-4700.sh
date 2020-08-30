$! /bin/bash

DELIMITER=" "

if [[ $# -eq 2 ]]
then
DELIMITER=${2}
elif [[ ! $# -eq 1 ]]
echo "invalid input"
exit 1
fi
REGEX="^[0-9]*$"
if [[ ! $1 =~ ${REGEX} ]]
then 
echo "Invalid integer"
fi

NUMCOUNT= $(echo $1 | wc -c )
REVNUM = $(echo $1 | rev)
for i in  ${REVNUM}
	
	if [ $((

