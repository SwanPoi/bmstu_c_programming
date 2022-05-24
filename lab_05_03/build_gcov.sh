#!/bin/bash
gcc -c main.c operations.c sort.c -std=c99 -Wall -Werror -Wpedantic -Wextra -g3 --coverage
gcc operations.o sort.o main.o --coverage -o app.exe
