#!/bin/bash

if [ "$3" != "" ]; then
  args=$(cat "$3")
else
  args=""
fi

if [ "$USE_VALGRIND" ]; then
  command="valgrind ../../app.exe $args < $1 > ../../outfile.txt"
else
  command="../../app.exe $args < $1 > ../../outfile.txt"
fi

if eval "$command"; then
  if ./comparator.sh "$2" ../../outfile.txt; then
    exit 0
  else
    exit 1
  fi
else
  exit 1
fi
