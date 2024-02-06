#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Usage: $0 filename"
  exit
fi

filename=$1

evenline=0

while read line; do
  evenline=$((evenline + 1))
  if [ $((evenline % 2)) -eq 0 ]; then
    echo "$line" >> evenfile
  else
    echo "$line" >> oddfile
  fi
done < $filename
