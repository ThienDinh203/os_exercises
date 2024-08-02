#!/bin/sh

echo "Enter your full name: "
read name

while [ "$name" = "" ]; do
  echo "Why do you not enter anything???" 
  read name
done

mkdir $name 

$(./revise_2b.sh $name)
exit 0
