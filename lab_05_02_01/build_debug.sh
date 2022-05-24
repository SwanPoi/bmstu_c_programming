#!/bin/bash
gcc -c main.c process.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -g3
gcc -o app.exe process.o main.o
