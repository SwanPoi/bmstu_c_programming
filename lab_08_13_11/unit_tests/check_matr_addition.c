#include <stdio.h>
#include "check_matr_addition.h"
#include "../inc/matrix_operations.h"
#include "../inc/matrix_IO.h"
#include "../inc/constants.h"
#include "../inc/struct.h"

// Сложение единичных матриц
START_TEST(addition_one_element_matrix)
{
    int rc = ERR_OK;
    double expected_res[1][1] = {{3}};

    matrix_t first_matrix;
    matrix_t second_matrix;

    first_matrix.data = NULL;
    second_matrix.data = NULL;

    first_matrix.rows = 1;
    second_matrix.rows = 1;

    first_matrix.columns = 1;
    second_matrix.columns = 1;

    rc = allocate_matrix(&first_matrix);

    ck_assert_ptr_nonnull(first_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    rc = allocate_matrix(&second_matrix);

    ck_assert_ptr_nonnull(second_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    first_matrix.data[0][0] = 1;
    second_matrix.data[0][0] = 2;

    matrix_t res_matrix;
    res_matrix.data = NULL;
    res_matrix.rows = 1;
    res_matrix.columns = 1;

    rc = matr_addition(&res_matrix, &first_matrix,&second_matrix);

    ck_assert_ptr_nonnull(res_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert_mem_eq(expected_res[0], res_matrix.data[0], 1 * sizeof(double));

    free_matrix(&first_matrix);
    free_matrix(&second_matrix);
    free_matrix(&res_matrix);
}
END_TEST

// Сложение матриц прямоугольных матриц
START_TEST(addition_rectangle_matrix)
{
    int rc = ERR_OK;
    double first[2][1] = {{4}, {1}};
    double second[2][1] = {{2}, {5}};
    double expected_res[2][1] = {{6}, {6}};

    matrix_t first_matrix;
    matrix_t second_matrix;

    first_matrix.data = NULL;
    second_matrix.data = NULL;

    first_matrix.rows = 2;
    second_matrix.rows = 2;

    first_matrix.columns = 1;
    second_matrix.columns = 1;

    rc = allocate_matrix(&first_matrix);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_ptr_nonnull(first_matrix.data);

    rc = allocate_matrix(&second_matrix);

    ck_assert_ptr_nonnull(second_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
    {
        memcpy(first_matrix.data[i], first[i], sizeof(double) * 1);
        memcpy(second_matrix.data[i], second[i], sizeof(double) * 1);
    }

    matrix_t res_matrix;
    res_matrix.data = NULL;
    res_matrix.rows = 2;
    res_matrix.columns = 1;

    rc = matr_addition(&res_matrix,&first_matrix, &second_matrix);

    ck_assert_ptr_nonnull(res_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        ck_assert_mem_eq(res_matrix.data[i], expected_res[i], 1 * sizeof(double));

    free_matrix(&first_matrix);
    free_matrix(&second_matrix);
    free_matrix(&res_matrix);
}
END_TEST

// Сложение матриц квадратных матриц
START_TEST(addition_square_matrix)
{
    int rc = ERR_OK;
    double first[2][2] = {{4, 3}, {1, 2}};
    double second[2][2] = {{2, 2}, {5, 7}};
    double expected_res[2][2] = {{6, 5}, {6, 9}};

    matrix_t first_matrix;
    matrix_t second_matrix;

    first_matrix.data = NULL;
    second_matrix.data = NULL;

    first_matrix.rows = 2;
    second_matrix.rows = 2;

    first_matrix.columns = 2;
    second_matrix.columns = 2;

    rc = allocate_matrix(&first_matrix);

    ck_assert_ptr_nonnull(first_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    rc  = allocate_matrix(&second_matrix);

    ck_assert_ptr_nonnull(second_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
    {
        memcpy(first_matrix.data[i], first[i], sizeof(double) * 2);
        memcpy(second_matrix.data[i], second[i], sizeof(double) * 2);
    }

    matrix_t res_matrix;
    res_matrix.data = NULL;
    res_matrix.rows = 2;
    res_matrix.columns = 2;

    rc = matr_addition(&res_matrix,&first_matrix, &second_matrix);

    ck_assert_ptr_nonnull(res_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        ck_assert_mem_eq(res_matrix.data[i], expected_res[i], 2 * sizeof(double));

    free_matrix(&first_matrix);
    free_matrix(&second_matrix);
    free_matrix(&res_matrix);
}
END_TEST

// Число строк первой матрицы не равно числу строк второй матрицы
START_TEST(unequal_rows_quantity_matrix)
{
    int rc = ERR_OK;
    double first[2][2] = {{4, 2}, {1, 5}};
    double second[1][2] = {{2, 5}};

    matrix_t first_matrix;
    matrix_t second_matrix;

    first_matrix.data = NULL;
    second_matrix.data = NULL;

    first_matrix.rows = 2;
    second_matrix.rows = 1;

    first_matrix.columns = 2;
    second_matrix.columns = 2;


    rc = allocate_matrix(&first_matrix);

    ck_assert_ptr_nonnull(first_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    rc = allocate_matrix(&second_matrix);

    ck_assert_ptr_nonnull(second_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        memcpy(first_matrix.data[i], first[i], sizeof(double) * 2);

    memcpy(second_matrix.data[0], second[0], sizeof(double) * 2);

    matrix_t res_matrix;
    res_matrix.data = NULL;
    res_matrix.rows = 2;
    res_matrix.columns = 2;

    rc = matr_addition(&res_matrix,&first_matrix, &second_matrix);

    ck_assert_ptr_null(res_matrix.data);
    ck_assert_int_eq(rc, ERR_DIFFERENT_SIZE_FOR_ADDITION);

    free_matrix(&first_matrix);
    free_matrix(&second_matrix);
}
END_TEST

// Число столбцов первой матрицы не равно числу столбцов второй матрицы
START_TEST(unequal_columns_count_matrix)
{
    int rc = ERR_OK;
    double first[1][3] = {{4, 2, 4}};
    double second[1][2] = {{2, 5}};

    matrix_t first_matrix;
    matrix_t second_matrix;

    first_matrix.data = NULL;
    second_matrix.data = NULL;

    first_matrix.rows = 1;
    second_matrix.rows = 1;

    first_matrix.columns = 3;
    second_matrix.columns = 2;

    rc = allocate_matrix(&first_matrix);

    ck_assert_ptr_nonnull(first_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    rc = allocate_matrix(&second_matrix);

    ck_assert_ptr_nonnull(second_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    memcpy(first_matrix.data[0], first[0], sizeof(double) * 3);
    memcpy(second_matrix.data[0], second[0], sizeof(double) * 2);

    matrix_t res_matrix;
    res_matrix.data = NULL;
    res_matrix.rows = 1;
    res_matrix.columns = 2;

    rc = matr_addition(&res_matrix, &first_matrix, &second_matrix);

    ck_assert_ptr_null(res_matrix.data);
    ck_assert_int_eq(rc, ERR_DIFFERENT_SIZE_FOR_ADDITION);

    free_matrix(&first_matrix);
    free_matrix(&second_matrix);
}
END_TEST

Suite *addition_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("addition_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, addition_one_element_matrix);
    tcase_add_test(tc_pos, addition_rectangle_matrix);
    tcase_add_test(tc_pos, addition_square_matrix);

    tc_neg = tcase_create("negatives");

    //Добавление негативных тестов
    tcase_add_test(tc_neg, unequal_rows_quantity_matrix);
    tcase_add_test(tc_neg, unequal_columns_count_matrix);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
