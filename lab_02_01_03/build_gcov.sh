#!/bin/bash
gcc -c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -g3 --coverage
gcc main.o --coverage -o app.exe -lm 
