#!/bin/bash
gcc -c search_sort_del.c read_write_structure.c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion
gcc -o app.exe search_sort_del.o read_write_structure.o main.o
