#!/bin/bash

filename="$1"

if [ ! -e "$filename" ]; then
    echo "Error: File not found."
    exit 1
fi

permissions=$(ls -l "$filename" | cut -d ' ' -f 1)
echo "Permissions for $filename: $permissions"
