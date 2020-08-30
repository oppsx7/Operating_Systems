#! /bin/bash

if [[ ! $# -eq 3 ]]
then
echo "Invalid input"
exit 1
fi

if [[ ! -d $1 || ! -d $2 ]]
then
echo "Not a directory"
exit 2
fi

if [[ ! $(ls -A ${2} | wc -l | awk '{$1=$1};1') -eq 0 ]]
then
echo "Dir2 contains files"
exit 3
fi

if [[ ! $(id -u) -eq 0 ]]
then
echo "Not a root user"
exit 4
fi
SRC=${1}
DEST=${2}
REGEX=".*txt$"
COMMAND="${DEST}"
find ${SRC} -type f | grep ${3} | while
read line
do
echo ${line} | tr '/' '\n'| tail -n +2 | while
read inner_line
do

COMMAND=${COMMAND}/${inner_line}
if [[ ${inner_line} =~ ${REGEX} ]]
then
touch ${COMMAND}
rm ${line}
else
mkdir $COMMAND
fi
done
done
