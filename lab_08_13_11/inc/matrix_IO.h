#ifndef LAB_08_MATRIX_IO_H
#define LAB_08_MATRIX_IO_H

#include "struct.h"

void free_matrix(matrix_t *matrix);
int allocate_matrix(matrix_t *matrix);
int input_size(FILE *file, int *rows, int *columns);
int input_matrix(FILE *file, matrix_t *matrix);
void output_matrix(FILE *file, matrix_t *matrix);
int matrix_preprocessing(FILE *file, matrix_t *matrix);
void matrix_init(matrix_t *matrix);
int write_matrix_to_file(char *res_name, matrix_t *matrix);

#endif //LAB_08_MATRIX_IO_H
