#ifndef LAB_08_MATRIX_OPERATIONS_H
#define LAB_08_MATRIX_OPERATIONS_H

double **matr_addition(double **first_matr, double **second_matr, int first_rows, int first_columns, int second_rows, int second_columns, int *code);
double **matr_multiplication(double **first_matr, double **second_matr, int first_rows, int first_columns, int second_rows, int second_columns, int *code);
double matrix_determinant(double **matr, int rows, int columns, int *rows_array, int *size, int start_column);
int search_in_arr(int *arr, int size, int elem);

#endif //LAB_08_MATRIX_OPERATIONS_H
