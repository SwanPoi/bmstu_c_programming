#include <stdlib.h>
#include "check_copy_names_startswith.h"
#include "../inc/process.h"
#include "../inc/struct.h"

// Все элементы массива подходят по началу названия
START_TEST(test_all_startswith)
{
    thing_t src[3] = {{"Poi", 20, 40}, {"Pony", 10, 30}, {"Pod", 12, 12}};
    thing_t res[3] = {{"Poi", 20, 40}, {"Pony", 10, 30}, {"Pod", 12, 12}};
    thing_t dst[3];

    size_t count = copy_names_startswith(src, dst, 3, "Po");

    ck_assert_int_eq(count, 3);

    for (int i = 0; i < 3; i++)
    {
        ck_assert_str_eq(res[i].name, dst[i].name);
        ck_assert_double_eq(res[i].weight, dst[i].weight);
        ck_assert_double_eq(res[i].volume, dst[i].volume);

        free(dst[i].name);
    }
}
END_TEST

// Несколько элементов массива подходят по началу названия
START_TEST(test_some_startswith)
{
    thing_t src[3] = {{"Poi", 20, 40}, {"Drop", 10, 30}, {"Pod", 12, 12}};
    thing_t res[2] = {{"Poi", 20, 40}, {"Pod", 12, 12}};
    thing_t dst[2];

    size_t count = copy_names_startswith(src, dst, 3, "Po");

    ck_assert_int_eq(count, 2);

    for (int i = 0; i < 2; i++)
    {
        ck_assert_str_eq(res[i].name, dst[i].name);
        ck_assert_double_eq(res[i].weight, dst[i].weight);
        ck_assert_double_eq(res[i].volume, dst[i].volume);

        free(dst[i].name);
    }
}
END_TEST

// Ни одно название не начинается с подстроки
START_TEST(test_all_not_startswith)
{
    thing_t src[3] = {{"Poi", 20, 40}, {"Pony", 10, 30}, {"Pod", 12, 12}};
    thing_t dst[3];

    size_t count = copy_names_startswith(src, dst, 3, "Dre");

    ck_assert_int_eq(count, 0);
}
END_TEST

Suite *copy_names_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("copy_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_all_startswith);
    tcase_add_test(tc_pos, test_some_startswith);

    tc_neg = tcase_create("negatives");

    //Добавление негативных тестов
    tcase_add_test(tc_neg, test_all_not_startswith);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
