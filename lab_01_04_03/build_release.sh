#!/bin/bash
gcc -c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra
gcc -o app.exe main.o
