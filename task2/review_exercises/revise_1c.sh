#!/bin/sh
count=0

for file in ./OS_LAB2_IMG/*.jpg
do
  mv $file ~/JPG/
done
echo "Its maybe work! "

for file in ~/JPG/*.jpg
do
  count=$(($count + 1))
done
echo "we have "$count" file"
exit 0
