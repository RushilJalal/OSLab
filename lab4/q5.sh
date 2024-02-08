#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <input_file> <pattern1> [pattern2 pattern3 ...]"
    exit 1
fi

input_file=$1
shift

while true; do
    echo "Menu:"
    echo "a. Search patterns in the input file"
    echo "b. Delete occurrences of patterns in the input file"
    echo "c. Exit"

    read -p "Enter your choice (a/b/c): " choice

    case $choice in
        a)
            for pattern in "$@"; do
                grep -n "$pattern" "$input_file"
            done
            ;;
        b)
            for pattern in "$@"; do
                sed -i "/$pattern/d" "$input_file"
            done
            echo "Deletions complete."
            ;;
        c)
            echo "Exiting the script."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter 'a', 'b', or 'c'."
            ;;
    esac
done

