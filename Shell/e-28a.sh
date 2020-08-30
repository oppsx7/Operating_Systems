#! /bin/bash

REGEX="^-?[0-9]*$"
mktemp tempFile.txt
while IFS= read -r line
do
if [[ ${line} =~ ${REGEX} ]]
then
echo ${line} >> tempFile.txt
fi
done
MIN=$(cat tempFile.txt | sort -n | uniq -c | sort -n | awk '{$1=$1};1' | grep "^1" | cut -d ' ' -f 2 | head -n 1)
MAX=$(cat tempFile.txt | sort -n | uniq -c | sort -n | awk '{$1=$1};1' | grep "^1" | cut -d ' ' -f 2 | tail -n 1)

if [[ $(echo $MIN | tr '-' ' ' | awk '{$1=$1};1') -gt $(echo $MAX | tr '-' ' ' | awk  '{$1=$1};1') ]]
then
echo ${MIN}
elif [[ $(echo $MIN | tr '-' ' ' | awk '{$1=$1};1') -lt $(echo $MAX | tr '-' ' ' | awk '{$1=$1};1') ]]
then
echo ${MAX}
else 
echo ${MIN}
echo ${MAX}
fi

rm tempFile.txt
