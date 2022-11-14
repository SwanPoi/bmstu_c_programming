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

    rc = matr_multiplication(&res_matrix,&first_matrix, &second_matrix);

    ck_assert_ptr_nonnull(res_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert_mem_eq(expected_res[0], res_matrix.data[0], 1 * sizeof(double));

    free_matrix(&first_matrix);
    free_matrix(&second_matrix);
    free_matrix(&res_matrix);
}
END_TEST

// Умножение матриц разных размеров
START_TEST(dif_size_matrix)
{
    int rc = ERR_OK;
    double first[2][1] = {{4}, {1}};
    double second[1][2] = {{2, 5}};
    double expected_res[2][2] = {{8, 20}, {2, 5}};

    matrix_t first_matrix;
    matrix_t second_matrix;

    first_matrix.data = NULL;
    second_matrix.data = NULL;

    first_matrix.rows = 2;
    second_matrix.rows = 1;

    first_matrix.columns = 1;
    second_matrix.columns = 2;

    rc = allocate_matrix(&first_matrix);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_ptr_nonnull(first_matrix.data);

    rc = allocate_matrix(&second_matrix);

    ck_assert_ptr_nonnull(second_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        memcpy(first_matrix.data[i], first[i], sizeof(double) * 1);

    memcpy(second_matrix.data[0], second[0], sizeof(double) * 2);

    matrix_t res_matrix;
    res_matrix.data = NULL;
    res_matrix.rows = 2;
    res_matrix.columns = 2;

    rc = matr_multiplication(&res_matrix,&first_matrix, &second_matrix);

    ck_assert_ptr_nonnull(res_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        ck_assert_mem_eq(res_matrix.data[i], expected_res[i], 2 * sizeof(double));

    free_matrix(&first_matrix);
    free_matrix(&second_matrix);
    free_matrix(&res_matrix);
}
END_TEST


// Число столбцов первой матрицы не равно числу строк второй матрицы
START_TEST(unsuitable_size_matrix)
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

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_ptr_nonnull(first_matrix.data);

    rc = allocate_matrix(&second_matrix);

    ck_assert_ptr_nonnull(second_matrix.data);
    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        memcpy(first_matrix.data[i], first[i], sizeof(double) * 2);

    memcpy(second_matrix.data[0], second[0], sizeof(double) * 2);

    matrix_t res_matrix;
    res_matrix.data = NULL;

    rc = matr_multiplication(&res_matrix,&first_matrix, &second_matrix);

    ck_assert_ptr_null(res_matrix.data);
    ck_assert_int_eq(rc, ERR_WRONG_SIZE_FOR_MULTIPLICATION);

    free_matrix(&first_matrix);
    free_matrix(&second_matrix);
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
