#!/bin/bash

find . -maxdepth 1 -type f -name "*.txt" | while read -r file
do
sed -e 's/^ex:/Example:/; s/\.ex:/Example:/' "$file"
done
