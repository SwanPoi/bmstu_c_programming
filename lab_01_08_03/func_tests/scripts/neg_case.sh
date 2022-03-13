#!/bin/bash

if [ "$2" != "" ]; then
  args=$(cat "$2")
else
  args=""
fi

if [ "$USE_VALGRIND" ]; then
  command="valgrind ../../app.exe $args < $1 > ../../outfile.txt"
else
  command="../../app.exe $args < $1 > ../../outfile.txt"
fi

if eval "$command"; then
  exit 1
else
  exit 0
fi
