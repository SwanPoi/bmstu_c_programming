#!/bin/bash

function del_nulls()
{
  pattern_nulls="0*$"
  pattern_point="\.$"
  for number in $1;
  do
    if [ "$number" == ".*\.0*$" ]; then
      number=${number//$pattern_nulls}
      number=${number//$pattern_point}
    fi
  done
}

if [[ $# -ne 2 ]]; then
  exit 1
fi

left_answer=$(grep -Eo "[-+]?[0-9]*[.]?[0-9]+" "$1")
right_answer=$(grep -Eo "[-+]?[0-9]*[.]?[0-9]+" "$2")

first_answer=$(del_nulls "$left_answer")
second_answer=$(del_nulls "$right_answer")

if [[ "$first_answer" == "$second_answer" ]]; then
  exit 0
fi
exit 1 
