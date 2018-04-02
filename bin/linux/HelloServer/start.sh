#!/bin/sh 
export LC_ALL="C"
ulimit -c unlimited
CURRENT_USER=$(whoami)
if [ -f "./sql_share" ];then
   SHARE_MEM_KEY=$(cat sql_share)
    for i in `ipcs -m | grep ${CURRENT_USER} | awk '{print $2}'`;
    do
     if [ $i != $SHARE_MEM_KEY ];then
      ipcrm -m $i
     fi
    done

    for i in `ipcs -m | grep ${CURRENT_USER} | awk '{print $2}'`;
    do
     if [ $i != $SHARE_MEM_KEY ];then
      ipcrm -s $i
     fi
    done
 else
    for i in `ipcs -m | grep ${CURRENT_USER} | awk '{print $2}'`;
     do
      ipcrm -m $i
     done

    for i in `ipcs -m | grep ${CURRENT_USER} | awk '{print $2}'`;
     do 
      ipcrm -s $i
    done
fi


rm -fv /tmp/*.bce
rm -fv /tmp/*.cs
rm -fv /tmp/*.dm
rm -fv /tmp/*.fdb
rm -fv /tmp/*.in
rm -fv /tmp/*.rs
rm -fv /tmp/*.us
rm -fv /tmp/*.ws


export LD_LIBRARY_PATH=./lib/:$LD_LIBRARY_PATH  
chmod 755 HelloServer
nohup ./HelloServer &
echo "start HelloServer success" 
