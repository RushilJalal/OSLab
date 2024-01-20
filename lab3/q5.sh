#!/bin/bash

echo -n  "Enter file extension "
read ext
echo -n "Enter destination folder "
read folder

if [ ! -d "$folder" ]
then
mkdir "$folder"
fi

find . -maxdepth 1 -type f -name "*$ext" | while read -r file 
do
cp -v "$file" "$folder/"
echo "copied $file to $folder"
done
