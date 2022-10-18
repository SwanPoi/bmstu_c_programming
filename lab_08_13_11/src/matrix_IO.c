#include <stdio.h>
#include <stdlib.h>
#include "../inc/matrix_IO.h"
#include "../inc/constants.h"

// Освобождение памяти из-под матрицы
void free_matrix(double **matr, int rows)
{
    for (int i = 0; i < rows; i++)
        free(matr[i]);

    free(matr);
}

// Выделение памяти под матрицу
double **allocate_matrix(int rows, int columns, int *code)
{
    double **matr = calloc(rows, sizeof(double *));

    if (!matr)
        *code = ERR_ALLOCATE_MATRIX;
    else
    {
        for (int i = 0; i < rows; i++)
        {
            matr[i] = calloc(columns, sizeof(double));

            if (!matr[i])
            {
                free_matrix(matr, rows);
                *code = ERR_ALLOCATE_ROW;
            }
        }
    }

    return matr;
}

// Ввод размеров матрицы из файла
int input_size(FILE *file, int *rows, int *columns)
{
    int code = ERR_OK;

    if (fscanf(file, "%d%d", rows, columns) != 2)
        code = ERR_READ_SIZE;
    else if (*rows <= 0 || *columns <= 0)
        code = ERR_WRONG_SIZE;

    return code;
}

// Ввод матрицы из файла
int input_matrix(FILE *file, double **matr, int rows, int columns)
{
    int code = ERR_OK;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (fscanf(file, "%lf", matr[i] + j) != 1)
                code = ERR_READ_MATRIX;

    return code;
}

// Вывод матрицы в файл
void output_matrix(FILE *file, double **matr, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            fprintf(file, "%lf ", matr[i][j]);

        fprintf(file, "\n");
    }
}

// Предобработка матрицы
int matrix_preprocessing(FILE *file, double ***matrix, int *rows, int *columns)
{
    int code = ERR_OK;

    code = input_size(file, rows, columns);

    if (code == ERR_OK)
        *matrix = allocate_matrix(*rows, *columns, &code);

    if (code == ERR_OK)
        code = input_matrix(file, *matrix, *rows, *columns);

    if (code == ERR_READ_MATRIX)
        free_matrix(*matrix, *rows);

    return code;
}
