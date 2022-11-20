#!/bin/bash

code=0

if [ "$3" != "" ]; then
  args=$(cat "$3")
else
  args=""
fi

s=""
for i in $args; do
  if [ -f "../../${i}" ] || [ "../../${i}" == "../../out/out.txt" ]; then
    s="${s}../../${i} "
  else
    s="${s}${i} "
  fi;
done;


if [ "$USE_VALGRIND" ]; then
  command="valgrind -q --log-file=../../out/valgrind_message.txt ../../app.exe $s < $1 > ../../out/outfile.txt"
else
  command="../../app.exe $s < $1 > ../../out/outfile.txt"
fi

if eval "$command"; then
  if ./comparator.sh "$2" ../../out/outfile.txt; then
    if [ -s ../../out/valgrind_message.txt ]; then
        code=1
    else
        code=0
    fi
  else
    if [ -s ../../out/valgrind_message.txt ]; then
        code=2
    else
        code=3
    fi
  fi
else
  code=4
fi

exit $code
