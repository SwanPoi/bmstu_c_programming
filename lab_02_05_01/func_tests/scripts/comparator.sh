#!/bin/bash

if [[ $# -ne 2 ]]; then
  exit 1
fi

left_answer=$(grep -Eo "[-+]?[0-9]*[.]?[0-9]+" "$1")
right_answer=$(grep -Eo "[-+]?[0-9]*[.]?[0-9]+" "$2")

if [ "$left_answer" == "$right_answer" ]; then
  exit 0
fi
exit 1 
