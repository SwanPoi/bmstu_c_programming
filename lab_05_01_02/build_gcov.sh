#!/bin/bash
gcc -c main.c process.c -std=c99 -Wall -Werror -Wpedantic -Wextra -g3 --coverage
gcc process.o main.o --coverage -o app.exe
