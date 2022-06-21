#!/bin/bash
gcc -c operations.c sort.c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra
gcc -o app.exe operations.o sort.o main.o
