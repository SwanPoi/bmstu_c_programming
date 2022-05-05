#!/bin/bash

first_answer=$(grep "^[[:alpha:]]+$" "$1")
second_answer=$(grep "^[[:alpha:]]+$" "$2")

if [ "$first_answer" == "$second_answer" ]; then
  exit 0
fi
exit 1
