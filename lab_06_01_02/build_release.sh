#!/bin/bash
gcc -c *.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
gcc -o app.exe *.o
