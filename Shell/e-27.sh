#! /bin/bash

if [[ ! $# -eq 2 ]]
then 
echo "invalid input"
exit 1
fi

if [[ ! -f $1 && ! -f $2 ]]
then
echo "not a file"
exit 2
fi
touch $2
cat $1 | cut -d ',' -f 2- | while 
read line
do
COUNT=$(cat $1 | grep ",${line}$" | wc -l | awk '{$1=$1};1') 
if [[ $(cat $2 | grep ",${line}$" | wc -l | awk '{$1=$1};1') -eq 0 ]]
then
if [[ $COUNT -gt 1 ]]
then
cat $1 | grep ",${line}$" | sort -n | head -n 1 >> $2
else 
cat $1 | grep ",$line$" >> $2
fi
fi
done

