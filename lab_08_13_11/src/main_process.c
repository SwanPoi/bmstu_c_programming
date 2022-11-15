#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/constants.h"
#include "../inc/matrix_IO.h"
#include "../inc/matrix_operations.h"
#include "../inc/main_process.h"

int det_process(char *src_name, char *dst_name)
{
    int rc = ERR_OK;
    FILE *src = fopen(src_name, "r");

    if (!src)
        rc = ERR_OPEN_FIRST_FILE;
    else
    {
        matrix_t matrix;

        matrix_init(&matrix);

        rc = input_size(src, &matrix.rows, &matrix.columns);

        if (matrix.rows != matrix.columns)
            rc = ERR_NOT_SQUARE_MATRIX;

        if (rc == ERR_OK)
        {
            rc = allocate_matrix(&matrix);

            array_t rows_array;
            array_init(&rows_array);

            rows_array.data = calloc(matrix.rows, sizeof(int));
            int start_column = 0;

            if (!rows_array.data)
                rc = ERR_DRAFT_ALLOC;

            if (rc == ERR_OK)
            {
                rc = input_matrix(src, &matrix);
                fclose(src);

                if (rc == ERR_OK)
                {
                    double det = matrix_determinant(&matrix, &rows_array, start_column, &rc);

                    if (rc == ERR_OK)
                        rc = print_det(dst_name, det);
                }
                free(rows_array.data);
            }
            else
            {
                matrix.rows = 0;
                matrix.columns = 0;
            }

            free_matrix(&matrix);
        }
    }

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
            matrix_t first_matrix, second_matrix, res_matrix;

            matrix_init(&first_matrix);
            matrix_init(&second_matrix);
            matrix_init(&res_matrix);

            // Обработка первой матрицы
            rc = matrix_preprocessing(first_file, &first_matrix);
            fclose(first_file);

            // Обработка второй матрицы
            if (rc == ERR_OK)
            {
                rc = matrix_preprocessing(second_file, &second_matrix);
                fclose(second_file);

                // Сложение или умножение матриц
                if (rc == ERR_OK)
                {
                    if (!strcmp(mode, "a"))
                        rc = matr_addition(&res_matrix, &first_matrix, &second_matrix);
                    else if (!strcmp(mode, "m"))
                        rc = matr_multiplication(&res_matrix, &first_matrix, &second_matrix);

                    free_matrix(&second_matrix);
                }
                free_matrix(&first_matrix);
            }

            // Вывод результата в файл
            if (rc == ERR_OK)
                rc = write_matrix_to_file(res_name, &res_matrix);

            free_matrix(&res_matrix);
        }
    }


    return rc;
}

int print_det(char *dst_name, double det)
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
