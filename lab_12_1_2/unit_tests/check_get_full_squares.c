#include "check_get_full_squares.h"

// Вместо исходного массива NULL
START_TEST(test_null_src_array)
{
    int size = 9;

    int rc = get_full_squares(NULL, 10, NULL, &size);

    ck_assert_int_eq(rc, ERR_NULL_POINTER);
}
END_TEST

// Вместо указателя на число элементов в результирующем массиве NULL
START_TEST(test_null_size)
{
    int arr[] = {1};

    int rc = get_full_squares(arr, 1, NULL, NULL);

    ck_assert_int_eq(rc, ERR_NULL_POINTER);
}
END_TEST

// Размер результирующего массива меньше числа полных квадратов
START_TEST(test_small_array)
{
    int arr[] = {4, 9, 16};
    int res[1];
    int size = 1;

    int rc = get_full_squares(arr, 3, res, &size);

    ck_assert_int_eq(rc, ERR_SMALL_ARRAY);
}
END_TEST

// Определение количества элементов в новом массиве
START_TEST(test_get_count)
{
    int arr[] = {4, 9, 16};
    int size = 0;

    int rc = get_full_squares(arr, 3, NULL, &size);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(size, 3);
}
END_TEST

// Массив без полных квадратов
START_TEST(test_no_squares)
{
    int arr[] = {3, 8, 19};
    int size = 0;

    int rc = get_full_squares(arr, 3, NULL, &size);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(size, 0);
}
END_TEST

// Запись полных квадратов в массив
START_TEST(test_write_squares)
{
    int arr[] = {4, 5, 16};
    int res[2];
    int expect[] = {4, 16};
    int size = 2;

    int rc = get_full_squares(arr, 3, res, &size);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(size, 2);

    ck_assert_mem_eq(expect, res, sizeof(res));
}
END_TEST

Suite *square_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("square_suite");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_get_count);
    tcase_add_test(tc_pos, test_no_squares);
    tcase_add_test(tc_pos, test_write_squares);
    tcase_add_test(tc_neg, test_null_src_array);
    tcase_add_test(tc_neg, test_null_size);
    tcase_add_test(tc_neg, test_small_array);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}