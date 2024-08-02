#!/bin/sh

if [ -z "$1" ]; then    # -z: True if the length of string is zero
  echo "You must enter folder behind your command line to run: "
else
    name=$1
    for file in $(cat ./monhoc.txt)
    do
      mkdir -p $name/$file   
    done
fi
exit 0
