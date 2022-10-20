#include <stdio.h>
#include "check_matr_multiplication.h"
#include "../inc/matrix_operations.h"
#include "../inc/matrix_IO.h"
#include "../inc/constants.h"

// Умножение единичных матриц
START_TEST(multiplication_one_el_matrix)
{
    int rc = ERR_OK;
    double expected_res[1][1] = {{2}};

    double **first_matrix = allocate_matrix(1, 1, &rc);
    double **second_matrix = allocate_matrix(1, 1, &rc);

    ck_assert_ptr_nonnull(first_matrix);
    ck_assert_ptr_nonnull(second_matrix);
    ck_assert_int_eq(rc, ERR_OK);

    first_matrix[0][0] = 1;
    second_matrix[0][0] = 2;

    double **res = matr_multiplication(first_matrix, second_matrix, 1, 1, 1, 1, &rc);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert_mem_eq(expected_res[0], res[0], 1 * sizeof(double));

    free_matrix(first_matrix, 1);
    free_matrix(second_matrix, 1);
    free_matrix(res, 1);
}
END_TEST

// Умножение матриц разных размеров
START_TEST(dif_size_matrix)
{
    int rc = ERR_OK;
    double first[2][1] = {{4}, {1}};
    double second[1][2] = {{2, 5}};
    double expected_res[2][2] = {{8, 20}, {2, 5}};

    double **first_matrix = allocate_matrix(2, 1, &rc);
    double **second_matrix = allocate_matrix(1, 2, &rc);

    ck_assert_ptr_nonnull(first_matrix);
    ck_assert_ptr_nonnull(second_matrix);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        memcpy(first_matrix[i], first[i], sizeof(double) * 1);

    memcpy(second_matrix[0], second[0], sizeof(double) * 2);

    double **res = matr_multiplication(first_matrix, second_matrix, 2, 1, 1, 2, &rc);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        ck_assert_mem_eq(res[i], expected_res[i], 2 * sizeof(double));

    free_matrix(first_matrix, 2);
    free_matrix(second_matrix, 1);
    free_matrix(res, 2);
}
END_TEST


// Число столбцов первой матрицы не равно числу строк второй матрицы
START_TEST(unsuitable_size_matrix)
{
    int rc = ERR_OK;
    double first[2][2] = {{4, 2}, {1, 5}};
    double second[1][2] = {{2, 5}};

    double **first_matrix = allocate_matrix(2, 2, &rc);
    double **second_matrix = allocate_matrix(1, 2, &rc);

    ck_assert_ptr_nonnull(first_matrix);
    ck_assert_ptr_nonnull(second_matrix);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        memcpy(first_matrix[i], first[i], sizeof(double) * 2);

    memcpy(second_matrix[0], second[0], sizeof(double) * 2);

    double **res = matr_multiplication(first_matrix, second_matrix, 2, 2, 1, 2, &rc);

    ck_assert_ptr_null(res);
    ck_assert_int_eq(rc, ERR_WRONG_SIZE_FOR_MULTIPLICATION);

    free_matrix(first_matrix, 2);
    free_matrix(second_matrix, 1);
}
END_TEST

Suite *multiplication_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("multiplication_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, multiplication_one_el_matrix);
    tcase_add_test(tc_pos, dif_size_matrix);

    tc_neg = tcase_create("negatives");

    //Добавление негативных тестов
    tcase_add_test(tc_neg, unsuitable_size_matrix);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}