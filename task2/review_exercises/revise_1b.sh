#!/bin/sh
count=0

for file in ./OS_LAB2_IMG/*.png
do
  mv $file ~/PNG/
done
echo "Its maybe work"

for file in ~/PNG/*.png
do
  count=$(($count + 1))
done
echo "we have "$count" file"
exit 0

