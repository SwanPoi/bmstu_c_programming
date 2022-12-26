#include <stdlib.h>
#include "check_left_k_shift.h"

// Негатив: вместо массива передан NULL
START_TEST(test_null_array)
{
    int rc = left_k_shift(NULL, 3, 1);

    ck_assert_int_eq(rc, ERR_NULL_POINTER);
}
END_TEST

// Массив из одного элемента
START_TEST(test_one_element)
{
    int arr[] = {1};
    int expect[] = {1};

    int rc = left_k_shift(arr, 1, 1);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(arr[0], expect[0]);

}
END_TEST

// Нулевой сдвиг
START_TEST(test_null_shift)
{
    int arr[] = {1, 2};
    int expect[] = {1, 2};

    int rc = left_k_shift(arr, 2, 0);

    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        ck_assert_int_eq(arr[i], expect[i]);
}
END_TEST

// После сдвига массив неизменен
START_TEST(test_full_circle_shift)
{
    int arr[] = {1, 2};
    int expect[] = {1, 2};

    int rc = left_k_shift(arr, 2, 2);

    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < 2; i++)
        ck_assert_int_eq(arr[i], expect[i]);
}
END_TEST

// Произвольный сдвиг
START_TEST(test_shift)
{
    int arr[] = {1, 2, 3, 4};
    int expect[] = {3, 4, 1, 2};
    int size = 4;

    int rc = left_k_shift(arr, size, 2);

    ck_assert_int_eq(rc, ERR_OK);

    for (int i = 0; i < size; i++)
        ck_assert_int_eq(arr[i], expect[i]);
}
END_TEST


Suite *shift_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("shift_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_one_element);
    tcase_add_test(tc_pos, test_null_shift);
    tcase_add_test(tc_pos, test_full_circle_shift);
    tcase_add_test(tc_pos, test_shift);

    tc_neg = tcase_create("negatives");

    //Добавление негативных тестов
    tcase_add_test(tc_neg, test_null_array);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}

