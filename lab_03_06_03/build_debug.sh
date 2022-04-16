#!/bin/bash
gcc -c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g3
gcc -o app.exe main.o
