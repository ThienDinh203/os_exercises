#!/bin/sh

name=$1
for file in $(cat ./monhoc.txt)
do
  mkdir -p $name/$file   
done
exit 0
