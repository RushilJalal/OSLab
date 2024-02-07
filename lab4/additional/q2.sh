#!/bin/bash

start_year=$1
end_year=$2
if [[ ! $start_year =~ ^[0-9]{4}$ || ! $end_year =~ ^[0-9]{4}$ ]]; then
  echo "Invalid year format. Please use YYYY."
  exit 1
fi

if [[ $start_year -gt $end_year ]]; then
  echo "Start year must be less than or equal to end year."
  exit 1
fi

find . -type f -newerct "$start_year-01-01 00:00:00" ! -newerct "$end_year-12-31 23:59:59" -print
