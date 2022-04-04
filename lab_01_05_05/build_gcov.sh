#!/bin/bash
gcc -c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra -g3 --coverage
gcc main.o --coverage -o app.exe -lm 
