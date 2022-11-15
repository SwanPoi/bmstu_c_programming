#include <stdio.h>
#include <stdlib.h>
#include "../inc/matrix_IO.h"
#include "../inc/constants.h"
#include "../inc/struct.h"

// Освобождение памяти из-под матрицы
void free_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
        free(matrix->data[i]);

    free(matrix->data);
}

// Выделение памяти под матрицу
int allocate_matrix(matrix_t *matrix)
{
    int code = ERR_OK;

    if (matrix != NULL)
    {
        matrix->data = calloc(matrix->rows, sizeof(double *));

        if (!matrix->data)
            code = ERR_ALLOCATE_MATRIX;
        else
        {
            for (int i = 0; i < matrix->rows; i++)
            {
                matrix->data[i] = calloc(matrix->columns, sizeof(double));

                if (!matrix->data[i])
                {
                    free_matrix(matrix);
                    code = ERR_ALLOCATE_ROW;
                }
            }
        }
    }
    else
        code = ERR_NULL;

    return code;
}

// Ввод размеров матрицы из файла
int input_size(FILE *file, int *rows, int *columns)
{
    int code = ERR_OK;

    if (file != NULL && rows != NULL && columns != NULL)
    {
        if (fscanf(file, "%d%d", rows, columns) != 2)
            code = ERR_READ_SIZE;
        else if (*rows <= 0 || *columns <= 0)
            code = ERR_WRONG_SIZE;
    }
    else
        code = ERR_NULL;

    return code;
}

// Ввод матрицы из файла
int input_matrix(FILE *file, matrix_t *matrix)
{
    int code = ERR_OK;

    if (file != NULL && matrix != NULL)
    {
        for (int i = 0; i < matrix->rows; i++)
            for (int j = 0; j < matrix->columns; j++)
                if (fscanf(file, "%lf", matrix->data[i] + j) != 1)
                    code = ERR_READ_MATRIX;
    }
    else
        code = ERR_NULL;

    return code;
}

// Вывод матрицы в файл
void output_matrix(FILE *file, matrix_t *matrix)
{
    if (file != NULL && matrix != NULL)
        for (int i = 0; i < matrix->rows; i++)
        {
            for (int j = 0; j < matrix->columns; j++)
                fprintf(file, "%lf ", matrix->data[i][j]);

            fprintf(file, "\n");
        }
}

// Предобработка матрицы
int matrix_preprocessing(FILE *file, matrix_t *matrix)
{
    int code = ERR_OK;

    if (file != NULL && matrix != NULL)
    {
        code = input_size(file, &matrix->rows, &matrix->columns);

        if (code == ERR_OK)
            code = allocate_matrix(matrix);

        if (code == ERR_OK)
            code = input_matrix(file, matrix);

        if (code == ERR_READ_MATRIX)
        {
            free_matrix(matrix);
            matrix->rows = 0;
        }
    }
    else
        code = ERR_NULL;

    return code;
}

// Инициализация матрицы
void matrix_init(matrix_t *matrix)
{
    matrix->data = NULL;
    matrix->rows = 0;
    matrix->columns = 0;
}

int write_matrix_to_file(char *res_name, matrix_t *matrix)
{
    int rc = ERR_OK;

    if (res_name != NULL && matrix != NULL)
    {
        FILE *res_file = fopen(res_name, "w");

        if (!res_file)
            rc = ERR_OPEN_RES_FILE;
        else
        {
            fprintf(res_file, "%d %d\n", matrix->rows, matrix->columns);
            output_matrix(res_file, matrix);
            fclose(res_file);
        }
    }
    else
        rc = ERR_NULL;

    return rc;
}
