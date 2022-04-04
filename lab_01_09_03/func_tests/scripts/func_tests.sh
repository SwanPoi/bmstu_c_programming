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
  
  if ./pos_case.sh "$in_file" "$out_file" "$args_file"; then
    echo -en "$GREEN""TEST""$counter"" PASSED!""$STANDART"
  else
    echo -en "$RED""TEST""$counter"" FAILED!""$STANDART"
    failed+=1
  fi
  
done
echo -en "$ORANGE""################################""$STANDART"


echo -en "$ORANGE""######## NEGATIVE TESTS ########""$STANDART"
for ((counter=1; counter <= neg_tests; counter++));
do
  in_file="../data/"$(find ../data | grep -Eo "neg_[0]?""$counter""_in.txt")
  
  if [ "$(find ../data | grep -Po "neg_[0]?""$counter""_args.txt" | wc -l)" -eq 1 ]; then
    args_file="../data/"$(find ../data | grep -Eo "neg_[0]?""$counter""_args.txt")
  else
    args_file=""
  fi
  
  
  if ./neg_case.sh "$in_file" "$args_file"; then
    echo -en "$GREEN""TEST""$counter"" PASSED!""$STANDART"
  else
    echo -en "$RED""TEST""$counter"" FAILED!""$STANDART"
    failed+=1
  fi
  
done
echo -en "$ORANGE""################################""$STANDART"

exit $failed
