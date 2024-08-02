#!/bin/sh

if [ -d "PNG" ]
then
  echo "PNG already exists"
else
  mkdir -p ~/PNG
  echo "Make dir PNG success"
fi
  
if [ -d "JPG" ]
then
  echo "JNG already exists"
else
  mkdir -p ~/JPG
  echo "Make dir JPG success"
fi
exit 0
