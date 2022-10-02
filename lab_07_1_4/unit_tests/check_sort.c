#include "check_sort.h"
#include "../inc/sort.h"

// Упорядоченный массив
START_TEST(test_sorted_array)
{
    int arr[] = {1, 2, 3, 4, 5};
    int res_arr[] = {1, 2, 3, 4, 5};

    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), comp_int);

    ck_assert_mem_eq(arr, res_arr, sizeof(arr));
}
END_TEST

// Упорядоченный в обратном порядке массив
START_TEST(test_reversed_array)
{
    int arr[] = {5, 4, 3, 2, 1};
    int res_arr[] = {1, 2, 3, 4, 5};

    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), comp_int);

    ck_assert_mem_eq(arr, res_arr, sizeof(arr));
}
END_TEST

// Неупорядоченный массив
START_TEST(test_unordered_array)
{
    int arr[] = {3, -1, 1, 4, 6, 0};
    int res_arr[] = {-1, 0, 1, 3, 4, 6};

    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), comp_int);

    ck_assert_mem_eq(arr, res_arr, sizeof(arr));
}
END_TEST

// Массив с повторяющимися элементами
START_TEST(test_repeat_elements_array)
{
    int arr[] = {-2, -10, -2, 1, 0, 4, 1, 9};
    int res_arr[] = {-10, -2, -2, 0, 1, 1, 4, 9};

    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), comp_int);

    ck_assert_mem_eq(arr, res_arr, sizeof(arr));
}
END_TEST

// Массив из одинаковых элементов
START_TEST(test_same_elements_array)
{
    int arr[] = {2, 2, 2, 2};
    int res_arr[] = {2, 2, 2, 2};

    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), comp_int);

    ck_assert_mem_eq(arr, res_arr, sizeof(arr));
}
END_TEST

// Массив из одного элемента
START_TEST(test_one_element_array)
{
    int arr[] = {1};
    int res_arr[] = {1};

    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), comp_int);

    ck_assert_mem_eq(arr, res_arr, sizeof(arr));
}
END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("filter_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_sorted_array);
    tcase_add_test(tc_pos, test_reversed_array);
    tcase_add_test(tc_pos, test_unordered_array);
    tcase_add_test(tc_pos, test_same_elements_array);
    tcase_add_test(tc_pos, test_repeat_elements_array);
    tcase_add_test(tc_pos, test_one_element_array);

    suite_add_tcase(s, tc_pos);

    return s;
}