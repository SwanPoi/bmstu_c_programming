#ifndef LAB_08_MATRIX_OPERATIONS_H
#define LAB_08_MATRIX_OPERATIONS_H

#include "struct.h"

int matr_addition(matrix_t *res_matrix, matrix_t *first_matrix, matrix_t *second_matrix);
int matr_multiplication(matrix_t *res_matrix, matrix_t *first_matrix, matrix_t *second_matrix);
double matrix_determinant(matrix_t *matrix, array_t *rows_array, int start_column, int *code);
int search_in_arr(array_t *array, int elem);
void correct_matrix_addition(matrix_t *res_matrix, matrix_t *first_matrix, matrix_t *second_matrix);
void correct_matrix_multiplication(matrix_t *res_matrix, matrix_t *first_matrix, matrix_t *second_matrix);
void array_init(array_t *array);

#endif //LAB_08_MATRIX_OPERATIONS_H
