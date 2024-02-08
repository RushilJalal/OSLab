#!/bin/bash

custom_sort() {
    array=("$@")
    n="${#}"

    for ((i=0; i<n-1; i++)); do
        for ((j=0; j<n-i-1; j++)); do
            if [[ "${array[j]}" > "${array[j+1]}" ]]; then
                temp="${array[j]}"
                array[j]="${array[j+1]}"
                array[j+1]="$temp"
            fi
        done
    done
    echo "${array[@]}"
}

original_array=("$@")
sorted_array=($(custom_sort "${original_array[@]}"))

echo "Sorted strings: ${sorted_array[@]}"
