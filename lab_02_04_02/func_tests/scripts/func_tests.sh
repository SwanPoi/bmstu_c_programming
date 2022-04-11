#!/bin/bash

ORANGE="\033[33m"
GREEN="\033[32m"
RED="\033[31m"
STANDART="\033[0m\n"

pos_tests=$(find ../data -name "pos_*_in.txt" | wc -l)
neg_tests=$(find ../data -name "neg_*_in.txt" | wc -l)

failed=0

echo -en "$ORANGE""######## POSITIVE TESTS ########""$STANDART"
for ((counter=1; counter <= pos_tests; counter++));
do
  in_file="../data/"$(find ../data | grep -Eo "pos_[0]?""$counter""_in.txt")
  out_file="../data/"$(find ../data | grep -Eo "pos_[0]?""$counter""_out.txt")
  
  if [ "$(find ../data | grep -Po "pos_[0]?""$counter""_args.txt" | wc -l)" -eq 1 ]; then
    args_file="../data/"$(find ../data | grep -Eo "pos_[0]?""$counter""_args.txt")
  else
    args_file=""
  fi
  ./pos_case.sh "$in_file" "$out_file" "$args_file"
  code=$?
  if [ "$code" -eq 0 ]; then
    echo -en "$GREEN""TEST""$counter"" PASSED!""$STANDART"
    if [ "$USE_VALGRIND" ]; then
        echo -en "$GREEN""MEMORY PASSED!""$STANDART"
    fi
  else 
    if [ "$code" -eq 1 ]; then
        echo -en "$GREEN""TEST""$counter"" PASSED!""$STANDART"
        if [ "$USE_VALGRIND" ]; then
            echo -en "$RED""MEMORY FAILED!""$STANDART"
        fi
    fi
    if [ "$code" -eq 2 ]; then
        echo -en "$RED""TEST""$counter"" FAILED!""$STANDART"
        if [ "$USE_VALGRIND" ]; then
            echo -en "$RED""MEMORY FAILED!""$STANDART"
        fi
    fi
    if [ "$code" -eq 3 ]; then
        echo -en "$RED""TEST""$counter"" FAILED!""$STANDART"
        if [ "$USE_VALGRIND" ]; then
            echo -en "$GREEN""MEMORY PASSED!""$STANDART"
        fi
    fi
    if [ "$code" -eq 4 ]; then
        echo -en "$RED""TEST""$counter"" DIDN'T START!""$STANDART"
    fi

    failed+=1
  fi
  echo -en "$ORANGE""##############""$STANDART"
done


echo -en "$ORANGE""######## NEGATIVE TESTS ########""$STANDART"
for ((counter=1; counter <= neg_tests; counter++));
do
  in_file="../data/"$(find ../data | grep -Eo "neg_[0]?""$counter""_in.txt")
  
  if [ "$(find ../data | grep -Po "neg_[0]?""$counter""_args.txt" | wc -l)" -eq 1 ]; then
    args_file="../data/"$(find ../data | grep -Eo "neg_[0]?""$counter""_args.txt")
  else
    args_file=""
  fi
  
  ./neg_case.sh "$in_file" "$args_file"
  code=$?
  
  if [ "$code" -eq 0 ]; then
    echo -en "$GREEN""TEST""$counter"" PASSED!""$STANDART"
    if [ "$USE_VALGRIND" ]; then
        echo -en "$GREEN""MEMORY PASSED!""$STANDART"
    fi
  else 
    if [ "$code" -eq 1 ]; then
        echo -en "$GREEN""TEST""$counter"" PASSED!""$STANDART"
        if [ "$USE_VALGRIND" ]; then
            echo -en "$RED""MEMORY FAILED!""$STANDART"
        fi
    fi
    if [ "$code" -eq 2 ]; then
        echo -en "$RED""TEST""$counter"" FAILED!""$STANDART"
        if [ "$USE_VALGRIND" ]; then
            echo -en "$RED""MEMORY FAILED!""$STANDART"
        fi
    fi
    if [ "$code" -eq 3 ]; then
        echo -en "$RED""TEST""$counter"" FAILED!""$STANDART"
        if [ "$USE_VALGRIND" ]; then
            echo -en "$GREEN""MEMORY PASSED!""$STANDART"
        fi
    fi
    failed+=1
  fi
  echo -en "$ORANGE""##############""$STANDART"
done
echo -en "$ORANGE""######### TESTS FINISHED! ########""$STANDART"

exit $failed
