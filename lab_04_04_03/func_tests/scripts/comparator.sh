#!/bin/bash

if diff "$1" "$2" >> ../../mistakes.txt; then
  exit 0
fi
exit 1
