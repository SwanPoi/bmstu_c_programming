#!/bin/bash

first_out=$(cat "$1")
second_out=$(cat "$2")

pattern="*Result: "
first_answer=${first_out//$pattern}
second_answer=${second_out//$pattern}

if [ "$first_answer" == "$second_answer" ]; then
  exit 0
fi
exit 1
