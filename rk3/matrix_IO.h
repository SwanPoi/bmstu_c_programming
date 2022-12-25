#ifndef __MATRIX_IO_H

#define __MATRIX_IO_H

#include <stdio.h>

void free_matrix(int **matr, int rows);
int **allocate_matrix(int rows, int columns, int *code);
void input_matrix(FILE *file, int **matrix, int rows, int columns);
int count_size(FILE *file);
void print_matrix(int **matrix, int rows, int columns);

#endif // __MATRIX_IO_H
