#!/bin/bash
gcc -c *.c -std=c99 -Wall -Werror -Wpedantic -Wextra -g3 --coverage
gcc *.o --coverage -o app.exe
