#include <stdlib.h>
#include "../inc/filter.h"
#include "check_filter.h"
#include "../inc/constants.h"

// Указатель на начало больше указателя на конец массива
START_TEST(test_start_after_end)
{
    int arr[] = {2, 4, 3};
    const int *pstart = arr;
    const int *pend = pstart - 1;
    int *dst_start = NULL, *dst_end = NULL;

    int rc = key(pstart, pend, &dst_start, &dst_end);

    ck_assert_int_eq(rc, ERR_END_LESS_START);
    free(dst_start);
}
END_TEST

// Пустой массив на входе
START_TEST(test_start_equal_end)
{
    int arr[] = {2, 4, 3};
    int *dst_start = NULL, *dst_end = NULL;

    int rc = key(arr, arr, &dst_start, &dst_end);

    ck_assert_int_eq(rc, ERR_END_LESS_START);
    free(dst_start);
}
END_TEST

// Указатель на начало - нуль
START_TEST(test_start_is_null)
{
    int arr[] = {2, 4, 3};
    const int *pend = arr + sizeof(arr) / sizeof(int);
    int *dst_start = NULL, *dst_end = NULL;

    int rc = key(NULL, pend, &dst_start, &dst_end);

    ck_assert_int_eq(rc, ERR_NULL_POINTER);
    free(dst_start);
}
END_TEST

// Указатель на конец - нуль
START_TEST(test_end_is_null)
{
    int arr[] = {2, 4, 3};
    const int *pstart = arr;
    int *dst_start = NULL, *dst_end = NULL;

    int rc = key(pstart, NULL, &dst_start, &dst_end);

    ck_assert_int_eq(rc, ERR_NULL_POINTER);
    free(dst_start);
}
END_TEST

// После фильтрации - пустой массив
START_TEST(test_empty_array)
{
    int arr[] = {1, 1, 1};
    int *dst_start = NULL, *dst_end = NULL;

    int rc = key(arr, arr + sizeof(arr) / sizeof(int), &dst_start, &dst_end);

    ck_assert_int_eq(rc, ERR_EMPTY_FILTER_ARRAY);
    free(dst_start);
}
END_TEST

// Среднее арифметическое не совпадает ни с одним элементом
START_TEST(test_mean_not_in_arr)
{
    int arr[] = {1, 2, 3, 4};
    int res_arr[] = {3, 4};
    int *dst_start = NULL, *dst_end = NULL;

    int rc = key(arr, arr + sizeof(arr) / sizeof(int), &dst_start, &dst_end);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_mem_eq(res_arr, dst_start, sizeof(res_arr));
    free(dst_start);
}
END_TEST

// Среднее арифметическое совпадает с одним из элементов массива
START_TEST(test_mean_in_arr)
{
    int arr[] = {1, 2, 3};
    int res_arr[] = {3};
    int *dst_start = NULL, *dst_end = NULL;

    int rc = key(arr, arr + sizeof(arr) / sizeof(int), &dst_start, &dst_end);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_mem_eq(res_arr, dst_start, sizeof(res_arr));
    free(dst_start);
}
END_TEST

Suite *filter_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("filter_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_mean_not_in_arr);
    tcase_add_test(tc_pos, test_mean_in_arr);

    tc_neg = tcase_create("negatives");

    //Добавление негативных тестов
    tcase_add_test(tc_neg, test_start_after_end);
    tcase_add_test(tc_neg, test_start_equal_end);
    tcase_add_test(tc_neg, test_start_is_null);
    tcase_add_test(tc_neg, test_end_is_null);
    tcase_add_test(tc_neg, test_empty_array);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
