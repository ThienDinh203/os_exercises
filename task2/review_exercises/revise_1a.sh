#!/bin/sh

if [ ! -d ~/PNG/ ]
then 
  mkdir ~/PNG
  echo "Make dir PNG success"
else
  echo "PNG already exists"
fi
  
if [ ! -d ~/JPG/ ]
then
  mkdir ~/JPG
  echo "Make dir JPG success"
else
  echo "JNG already exists"
fi
exit 0
