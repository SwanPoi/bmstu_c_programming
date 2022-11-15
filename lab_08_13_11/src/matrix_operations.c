#include <stdio.h>
#include "../inc/matrix_operations.h"
#include "../inc/matrix_IO.h"
#include "../inc/constants.h"

// Сложение матриц
int matr_addition(matrix_t *res_matrix, matrix_t *first_matrix, matrix_t *second_matrix)
{
    int code = ERR_OK;

    if (res_matrix == NULL || first_matrix == NULL || second_matrix == NULL)
        code = ERR_NULL;
    else if (first_matrix->rows != second_matrix->rows || first_matrix->columns != second_matrix->columns)
        code = ERR_DIFFERENT_SIZE_FOR_ADDITION;

    if (code == ERR_OK)
    {
        res_matrix->rows = first_matrix->rows;
        res_matrix->columns = first_matrix->columns;

        code = allocate_matrix(res_matrix);

        if (code == ERR_OK)
            correct_matrix_addition(res_matrix, first_matrix, second_matrix);
    }

    return code;
}

// Умножение матриц
int matr_multiplication(matrix_t *res_matrix, matrix_t *first_matrix, matrix_t *second_matrix)
{
    int code = ERR_OK;

    if (res_matrix == NULL || first_matrix == NULL || second_matrix == NULL)
        code = ERR_NULL;
    else if (first_matrix->columns != second_matrix->rows)
        code = ERR_WRONG_SIZE_FOR_MULTIPLICATION;

    if (code == ERR_OK)
    {
        res_matrix->rows = first_matrix->rows;
        res_matrix->columns = second_matrix->columns;

        code = allocate_matrix(res_matrix);

        if (code == ERR_OK)
            correct_matrix_multiplication(res_matrix, first_matrix, second_matrix);
    }

    return code;
}

// Рекурсивное вычисление определителя разложением по столбцу
double matrix_determinant(matrix_t *matrix, array_t *rows_array, int start_column, int *code)
{
    double det = 0.0;
    int degree = 1;

    if (matrix == NULL || rows_array == NULL)
        *code = ERR_NULL;

    if (*code == ERR_OK && matrix->rows * matrix->columns == 1)
        det = matrix->data[0][0];
    else if (*code == ERR_OK && matrix->rows - rows_array->size == 2)
    {
        int first_row = 0, second_row = 0;

        for (int i = 0; i < matrix->rows; i++)
            if (search_in_arr(rows_array, i) == FALSE)
            {
                first_row = second_row;
                second_row = i;
            }

        det += matrix->data[first_row][start_column] * matrix->data[second_row][start_column + 1]
            - matrix->data[second_row][start_column] * matrix->data[first_row][start_column + 1];
    }
    else if (*code == ERR_OK)
    {
        for (int i = 0; i < matrix->rows; i++)
            if (search_in_arr(rows_array, i) == FALSE)
            {
                rows_array->data[rows_array->size] = i;
                (rows_array->size)++;

                det += degree * matrix->data[i][start_column] * matrix_determinant(matrix, rows_array, start_column + 1, code);
                degree *= -1;

                rows_array->data[(rows_array->size) - 1] = matrix->rows;
                (rows_array->size)--;
            }
    }

    return det;
}

// Поиск числа в массиве
int search_in_arr(array_t *array, int elem)
{
    int is_in_arr = FALSE;

    if (array != NULL)
        for (int i = 0; i < array->size && is_in_arr == FALSE; i++)
            if (array->data[i] == elem)
                is_in_arr = TRUE;

    return is_in_arr;
}

// Умножение корректных матриц
void correct_matrix_multiplication(matrix_t *res_matrix, matrix_t *first_matrix, matrix_t *second_matrix)
{
    for (int i = 0; i < first_matrix->rows; i++)
        for (int j = 0; j < second_matrix->columns; j++)
            for (int k = 0; k < first_matrix->columns; k++)
                res_matrix->data[i][j] += first_matrix->data[i][k] * second_matrix->data[k][j];
}

// Сложение корректных матриц
void correct_matrix_addition(matrix_t *res_matrix, matrix_t *first_matrix, matrix_t *second_matrix)
{
    for (int i = 0; i < first_matrix->rows; i++)
        for (int j = 0; j < first_matrix->columns; j++)
            res_matrix->data[i][j] = first_matrix->data[i][j] + second_matrix->data[i][j];
}

// Инициализация массива
void array_init(array_t *array)
{
    array->data = NULL;
    array->size = 0;
}
