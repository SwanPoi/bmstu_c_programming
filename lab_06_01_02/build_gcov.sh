#!/bin/bash
gcc -c *.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -g3 --coverage
gcc *.o --coverage -o app.exe
