#!/bin/bash

for i in {1..120}
do
  echo $i >> count.txt
  sleep 1
done
exit 0

