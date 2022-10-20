#include <stdio.h>
#include "../inc/matrix_operations.h"
#include "../inc/matrix_IO.h"
#include "../inc/constants.h"

// Сложение матриц
double **matr_addition(double **first_matr, double **second_matr, int first_rows, int first_columns, int second_rows, int second_columns, int *code)
{
    double **res_matr = NULL;

    if (first_rows != second_rows || first_columns != second_columns)
        *code = ERR_DIFFERENT_SIZE_FOR_ADDITION;

    if (*code == ERR_OK)
    {
        res_matr = allocate_matrix(first_rows, first_columns, code);

        if (*code == ERR_OK)
            correct_matrix_addition(res_matr, first_matr, second_matr, first_rows, first_columns);
    }

    return res_matr;
}

// Умножение матриц
double **matr_multiplication(double **first_matr, double **second_matr, int first_rows, int first_columns, int second_rows, int second_columns, int *code)
{
    double **res_matr = NULL;

    if (first_columns != second_rows)
        *code = ERR_WRONG_SIZE_FOR_MULTIPLICATION;

    if (*code == ERR_OK)
    {
        res_matr = allocate_matrix(first_rows, second_columns, code);

        if (*code == ERR_OK)
            correct_matrix_multiplication(res_matr, first_matr, first_rows, first_columns, second_matr, second_columns);
    }

    return res_matr;
}

// Рекурсивное вычисление определителя разложением по столбцу
double matrix_determinant(double **matr, int rows, int columns, int *rows_array, int *size, int start_column)
{
    double det = 0.0;
    int degree = 1;

    if (rows * columns == 1)
        det = matr[0][0];
    else if (rows - *size == 2)
    {
        int first_row = 0, second_row = 0;

        for (int i = 0; i < rows; i++)
            if (search_in_arr(rows_array, *size, i) == FALSE)
            {
                first_row = second_row;
                second_row = i;
            }

        det += matr[first_row][start_column] * matr[second_row][start_column + 1] - matr[second_row][start_column] * matr[first_row][start_column + 1];
    }
    else
    {
        for (int i = 0; i < rows; i++)
            if (search_in_arr(rows_array, *size, i) == FALSE)
            {
                rows_array[*size] = i;
                (*size)++;

                det += degree * matr[i][start_column] * matrix_determinant(matr, rows, columns, rows_array, size, start_column + 1);
                degree *= -1;

                rows_array[(*size) - 1] = rows;
                (*size)--;
            }
    }

    return det;
}

// Поиск числа в массиве
int search_in_arr(int *arr, int size, int elem)
{
    int is_in_arr = FALSE;

    for (int i = 0; i < size && is_in_arr == FALSE; i++)
        if (arr[i] == elem)
            is_in_arr = TRUE;

    return is_in_arr;
}

// Умножение корректных матриц
void correct_matrix_multiplication(double **res_matr, double **first_matr, int first_rows, int first_columns, double **second_matr, int second_columns)
{
    for (int i = 0; i < first_rows; i++)
        for (int j = 0; j < second_columns; j++)
            for (int k = 0; k < first_columns; k++)
                res_matr[i][j] += first_matr[i][k] * second_matr[k][j];
}

// Сложение корректных матриц
void correct_matrix_addition(double **res_matr, double **first_matr, double **second_matr, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            res_matr[i][j] = first_matr[i][j] + second_matr[i][j];
}
