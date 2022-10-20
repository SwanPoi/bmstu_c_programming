#include <stdio.h>
#include <stdlib.h>
#include "check_matrix_determinant.h"
#include "../inc/matrix_operations.h"
#include "../inc/matrix_IO.h"
#include "../inc/constants.h"

// Определитель матрицы 2 на 2
START_TEST(determinant_four_elements_matrix)
{
    int rc = ERR_OK;
    double expected_res = -10;
    double src[2][2] = {{1, 4}, {5, 10}};

    double **matrix = allocate_matrix(2, 2, &rc);
    int *draft_array = calloc(2, sizeof(int));

    ck_assert_ptr_nonnull(matrix);
    ck_assert_ptr_nonnull(draft_array);
    ck_assert_int_eq(rc, ERR_OK);

    draft_array[0] = 2;
    draft_array[1] = 3;

    for (int i = 0; i < 2; i++)
        memcpy(matrix[i], src[i], sizeof(double) * 2);

    int size = 0;

    double res = matrix_determinant(matrix, 2, 2, draft_array, &size, 0);

    ck_assert_double_eq(res, expected_res);

    free_matrix(matrix, 2);
    free(draft_array);
}
END_TEST

// Определитель единичной матрицы
START_TEST(determinant_one_element_matrix)
{
    int rc = ERR_OK;
    double expected_res= 3;

    double **matrix = allocate_matrix(1, 1, &rc);
    int *draft_array = calloc(1, sizeof(int));

    ck_assert_ptr_nonnull(matrix);
    ck_assert_ptr_nonnull(draft_array);
    ck_assert_int_eq(rc, ERR_OK);

    matrix[0][0] = 3;

    int size = 0;

    double res = matrix_determinant(matrix, 1, 1, draft_array, &size, 0);

    ck_assert_double_eq(res, expected_res);

    free_matrix(matrix, 1);
    free(draft_array);
}
END_TEST

// Определитель матрицы 3 на 3
START_TEST(determinant_nine_elements_matrix)
{
    int rc = ERR_OK;
    double expected_res = 2;
    double src[3][3] = {{1, 4, 5}, {5, 10, 2}, {3, 6, 1}};

    double **matrix = allocate_matrix(3, 3, &rc);
    int *draft_array = calloc(3, sizeof(int));

    ck_assert_ptr_nonnull(matrix);
    ck_assert_ptr_nonnull(draft_array);
    ck_assert_int_eq(rc, ERR_OK);

    draft_array[0] = 3;
    draft_array[1] = 4;
    draft_array[2] = 5;

    for (int i = 0; i < 3; i++)
        memcpy(matrix[i], src[i], sizeof(double) * 3);

    int size = 0;

    double res = matrix_determinant(matrix, 3, 3, draft_array, &size, 0);

    ck_assert_double_eq(res, expected_res);

    free_matrix(matrix, 3);
    free(draft_array);
}
END_TEST

Suite *determinant_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("determinant_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, determinant_four_elements_matrix);
    tcase_add_test(tc_pos, determinant_one_element_matrix);
    tcase_add_test(tc_pos, determinant_nine_elements_matrix);

    suite_add_tcase(s, tc_pos);

    return s;
}