#!/bin/bash
gcc -c process.c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra
gcc -o app.exe process.o main.o
