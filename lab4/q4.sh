#!/bin/bash

option=$1
filename=$2

if [ $# -lt 2 ]
then
echo "Format: -option -filename"
fi

case $option in 
-linecount)
wc -l < "$filename"
;;
-wordcount)
wc -w < "$filename"
;;
-charcount)
wc -c < "$filename"
;;
*)
esac
