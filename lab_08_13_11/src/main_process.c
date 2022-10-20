#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/constants.h"
#include "../inc/matrix_IO.h"
#include "../inc/matrix_operations.h"

int det_print(char *dst_name, double det)
{
    int rc = ERR_OK;
    FILE *dst = fopen(dst_name, "w");

    if (!dst)
        rc = ERR_OPEN_RES_FILE;
    else
    {
        fprintf(dst, "%lf\n", det);
        fclose(dst);
    }

    return rc;
}

double det_search(double **matrix, int rows, int columns, int *rc)
{
    double det = 0.0;
    int *draft_array = calloc(rows, sizeof(int));
    int draft_size = 0, start_column = 0;

    if (!draft_array)
        *rc = ERR_DRAFT_ALLOC;
    else
    {
        for (int i = 0; i < draft_size; i++)
            draft_array[i] = rows;

        det = matrix_determinant(matrix, rows, columns, draft_array, &draft_size, start_column);
    }

    free(draft_array);

    return det;
}

int det_process(char *src_name, char *dst_name)
{
    int rc = ERR_OK;
    FILE *src = fopen(src_name, "r");

    if (!src)
        rc = ERR_OPEN_FIRST_FILE;
    else
    {
        int rows = 0, columns = 0;

        rc = input_size(src, &rows, &columns);

        if (rows != columns)
            rc = ERR_NOT_SQUARE_MATRIX;

        if (rc == ERR_OK)
        {
            double **matrix = allocate_matrix(rows, columns, &rc);

            if (rc == ERR_OK)
            {
                double det = 0.0;

                rc = input_matrix(src, matrix, rows, columns);

                if (rc == ERR_OK)
                    det = det_search(matrix, rows, columns, &rc);

                if (rc == ERR_OK)
                    rc = det_print(dst_name, det);
            }

            free_matrix(matrix, rows);
        }

        fclose(src);
    }

    return rc;
}

int process_with_open_files(FILE *first_file, FILE *second_file, FILE *res_file, char *mode)
{
    int rc = ERR_OK;

    double **first_matrix = NULL;
    double **second_matrix = NULL;
    double **res_matrix = NULL;
    int first_rows = 0, second_rows = 0, first_columns = 0, second_columns = 0, res_rows = 0, res_columns = 0;

    rc = matrix_preprocessing(first_file, &first_matrix, &first_rows, &first_columns);

    if (rc == ERR_OK)
    {
        rc = matrix_preprocessing(second_file, &second_matrix, &second_rows, &second_columns);
        // Сложение или умножение матриц
        if (rc == ERR_OK)
        {
            if (!strcmp(mode, "a"))
            {
                res_matrix = matr_addition(first_matrix, second_matrix, first_rows, first_columns, second_rows, second_columns, &rc);

                if (rc == ERR_OK)
                {
                    res_rows = first_rows;
                    res_columns = first_columns;
                }
            }
            else if (!strcmp(mode, "m"))
            {
                res_matrix = matr_multiplication(first_matrix, second_matrix, first_rows, first_columns, second_rows, second_columns, &rc);

                if (rc == ERR_OK)
                {
                    res_rows = first_rows;
                    res_columns = second_columns;
                }
            }

            free_matrix(second_matrix, second_rows);
        }

        free_matrix(first_matrix, first_rows);
    }

    if (rc == ERR_OK)
    {
        fprintf(res_file, "%d %d\n", res_rows, res_columns);
        output_matrix(res_file, res_matrix, res_rows, res_columns);
    }

    free_matrix(res_matrix, res_rows);

    return rc;
}

int add_mult_process(char *first_name, char *second_name, char *res_name, char *mode)
{
    int rc = ERR_OK;
    FILE *first_file = fopen(first_name, "r");

    if (!first_file)
        rc = ERR_OPEN_FIRST_FILE;

    // Открытие второго файла
    if (rc == ERR_OK)
    {
        FILE *second_file = fopen(second_name, "r");

        if (!second_file)
            rc = ERR_OPEN_SECOND_FILE;
        else
        {
            FILE *res_file = fopen(res_name, "w");

            if (!res_file)
                rc = ERR_OPEN_RES_FILE;

            rc = process_with_open_files(first_file, second_file, res_file, mode);

            if (rc != ERR_OPEN_RES_FILE)
                fclose(res_file);

            fclose(second_file);
        }

        fclose(first_file);
    }

    return rc;
}
