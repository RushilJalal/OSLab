#!/bin/bash

filename="$1"
start_line="$2"
end_line="$3"

if [ ! -e "$filename" ]; then
    echo "Error: File not found."
    exit 1
fi

sed -n "${start_line},${end_line}p" "$filename"

