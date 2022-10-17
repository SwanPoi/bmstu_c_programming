#!/bin/bash
cd ./out
gcc -c ../src/*.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -g3
gcc -o ../app.exe *.o
cd ../
