#!/bin/bash

cd ./func_tests/scripts || exit
./func_tests.sh
cd ../../ || exit
gcov main.gcda
