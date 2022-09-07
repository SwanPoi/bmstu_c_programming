#!/bin/bash
gcc -c *.c -std=c99 -Wall -Werror -Wpedantic -Wextra -g3
gcc -o app.exe *.o
