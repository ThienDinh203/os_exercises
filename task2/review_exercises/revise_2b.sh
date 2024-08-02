#!/bin/sh

name=$1
for file in $(cat ./monhoc.txt)
do
  mkdir $name/$file   
done
exit 0
