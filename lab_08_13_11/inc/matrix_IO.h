#ifndef LAB_08_MATRIX_IO_H
#define LAB_08_MATRIX_IO_H

void free_matrix(double **matr, int rows);
double **allocate_matrix(int rows, int columns, int *code);
int input_size(FILE *file, int *rows, int *columns);
int input_matrix(FILE *file, double **matr, int rows, int columns);
void output_matrix(FILE *file, double **matr, int rows, int columns);
int matrix_preprocessing(FILE *file, double ***matrix, int *rows, int *columns);

#endif //LAB_08_MATRIX_IO_H
