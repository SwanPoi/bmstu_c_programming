#!/bin/bash

code=0

if [ "$3" != "" ]; then
  args=$(cat "$3")
else
  args=""
fi

if [ "$USE_VALGRIND" ]; then
  command="valgrind -q --log-file=../../valgrind_message.txt ../../app.exe ../../$args < $1 > ../../outfile.txt"
else
  command="../../app.exe ../../$args < $1 > ../../outfile.txt"
fi

if eval "$command"; then
  if ./comparator.sh "$2" ../../outfile.txt; then
    if [ -s ../../valgrind_message.txt ]; then
        code=1
    else
        code=0
    fi
  else
    if [ -s ../../valgrind_message.txt ]; then
        code=2
    else
        code=3
    fi
  fi
else
  code=4
fi

exit $code
