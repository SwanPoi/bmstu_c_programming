#!/bin/bash
gcc -c main.c process.c -std=c99 -Wall -Werror -Wpedantic -Wextra -g3
gcc -o app.exe process.o main.o
