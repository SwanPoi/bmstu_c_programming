#!/bin/bash
gcc -c rk2.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla
gcc -o app.exe rk2.o
