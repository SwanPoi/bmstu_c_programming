#!/bin/bash

if [[ $# -ne 2 ]]; then
  exit 1
fi

if diff "$1" "$2" > ../../diff.txt;  then
  exit 0
fi
exit 1 
