#!/bin/bash

echo -n "Enter a number: "
read number

if [ $number -le 0 ]; then
  echo "Factorial of $number is 1"
  exit
fi

factorial=1
for ((i=1; i<=$number; i++)); do
  factorial=$((factorial * i))
done

echo "Factorial of $number is $factorial"
