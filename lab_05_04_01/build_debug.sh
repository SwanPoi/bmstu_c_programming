#!/bin/bash
gcc -c operations.c delete_students.c sort_students.c search_startwith.c main.c -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -g3
gcc -o app.exe operations.o delete_students.o sort_students.o search_startwith.o main.o
