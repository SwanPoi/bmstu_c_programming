#!/bin/bash
gcc -c *.c -std=c99 -Wall -Werror -Wpedantic -Wextra
gcc -o app.exe *.o
