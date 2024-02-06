#!/bin/bash

filename=$1
extension=$(echo "$filename" | cut -d "." -f 2)
cp "$filename" "${filename}_copy.$extension"
echo "Created copy: ${filename}_copy.$extension"
