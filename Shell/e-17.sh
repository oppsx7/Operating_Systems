#! /bin/bash

if [[ ! $# -eq 1 ]]
then
echo "Invalid input"
exit 1
fi

if [[ $(id -u) -ne 0 ]]
then
echo "Please run as root"
exit 2
fi 

COUNT=$(ps -eo user,pid,time | sort | grep "${1}" | wc -l)
AVG=$(ps -eo time | tr '.' ':' | awk -F ':' 'BEGIN {total=0;} {total+=(($1*3600)+($2*60)+$3)} END {a=(total/NR);printf "%02d:%02d:%02d\n",(a/3600),(a/60%60),(a%60)}') 
echo "AVG: ${AVG}"
DOUBLE_AVG=$(echo ${AVG} | awk -F ':' 'BEGIN {total=0;} {total+=(($1*3600*2)+($2*60*2)+$3*2)}
END {print total}')
ps -eo user,pid,time | grep ${1} | while
read line
do
TIME=$(echo ${line} | awk '{$1=$1};1' | cut -d ' ' -f 3 | tr '.' ':' | awk -F ':' 'BEGIN {total=0;} {total+=(($1*3600)+($2*60)+$3)} END {print total}')

if [[ ${TIME} -gt ${DOUBLE_AVG} ]]
then
echo "pid: $(echo ${line} | awk '{$1=$1};1' | cut -d ' ' -f 2)"
fi

done
ps -eo user | sort | uniq -c | sort -n -r |  while
read line
do

if [[ ! $(echo ${line} | awk '{$1=$1};1' | cut -d ' ' -f 1) -gt ${COUNT} ]]
then
exit 0
fi
echo $(echo ${line} | awk '{$1=$1};1' | cut -d ' ' -f 2)
done

