#!/bin/bash

function custom_sort() {
  # Convert strings to lowercase for case-insensitive sorting
  lower_strings=($(echo "${@}" | tr '[:upper:]' '[:lower:]'))

  # Create a temporary file to store the sorted order of characters
  temp_file=$(mktemp)

  # Write each character followed by a newline to the temporary file,
  # ensuring unique characters and preserving order of first occurrence
  for string in "${lower_strings[@]}"; do
    echo "${string}" | tr -d '[:space:]' | sort -u >> "$temp_file"
  done

  # Create a dictionary to store the character order
  char_order=()
  while read -r char; do
    char_order+=("$char")
  done < "$temp_file"

  # Define a custom key function for sorting
  key_func() {
    string="${1,,}"  # Convert to lowercase for lookup
    local index=0
    for char in "${string}"; do
      index=$((index + ${char_order[(i)${char}]}))
    done
    echo "$index"
  }

  # Sort the original arguments using the custom key function
  sorted_strings=($(printf "%s\n" "${@}" | sort -t' ' -k1,1n -k2,2n -k3,3n -k4,4n --key=key_func))

  # Print the sorted strings
  echo "${sorted_strings[@]}"

  # Remove the temporary file
  rm "$temp_file"
}

# Get the command-line arguments
args=("$@")

# Sort the arguments using the custom_sort function
custom_sort "${args[@]}"
