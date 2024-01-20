#!/bin/bash

echo "Enter basic"
read basic
echo "TA=?"
read TA

GS=$(echo "$basic + $TA + 0.1 * $TA" | bc)
echo $GS
