#!/bin/bash
gcc -c main.c search_sort_del.c read_write_structure.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion -g3
gcc -o app.exe search_sort_del.o read_write_structure.o main.o
