#!/bin/bash

echo -n "Enter a number: "
read number

if [ $number -le 1 ]; then
  echo "$number is not a prime number."
  exit
fi

for ((i=2; i<=$number; i++)); do
  if [ $((number % i)) -eq 0 ]; then
    echo "$number is not a prime number."
    exit
  fi
done

echo "$number is a prime number."
