#!/bin/bash
gcc -c main.c operations.c sort.c -std=c99 -Wall -Werror -Wpedantic -Wextra -g3
gcc -o app.exe operations.o sort.o main.o
