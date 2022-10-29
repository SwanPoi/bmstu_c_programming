#include "check_sort_container.h"
#include "../inc/process.h"
#include "../inc/struct.h"

// Неотсортированный массив
START_TEST(test_not_sorted)
{
    thing_t src[3] = {{"Poi", 20, 40}, {"Pony", 10, 30}, {"Pod", 12, 12}};
    thing_t res[3] = {{"Pony", 10, 30}, {"Poi", 20, 40}, {"Pod", 12, 12}};

    sort_container(src, 3);

    for (int i = 0; i < 3; i++)
    {
        ck_assert_str_eq(res[i].name, src[i].name);
        ck_assert_double_eq(res[i].weight, src[i].weight);
        ck_assert_double_eq(res[i].volume, src[i].volume);
    }
}
END_TEST

// Неотсортированный массив с повторяющимися элементами
START_TEST(test_with_repeat)
{
    thing_t src[3] = {{"Poi", 20, 40}, {"Pod", 12, 12},{"Pony", 10, 20}};
    thing_t res[3] = {{"Poi", 20, 40}, {"Pony", 10, 20}, {"Pod", 12, 12}};

    sort_container(src, 3);

    for (int i = 0; i < 3; i++)
    {
        ck_assert_str_eq(res[i].name, src[i].name);
        ck_assert_double_eq(res[i].weight, src[i].weight);
        ck_assert_double_eq(res[i].volume, src[i].volume);
    }
}
END_TEST

// Отсортированный массив
START_TEST(test_sorted)
{
    thing_t src[3] = {{"Poi", 1, 40}, {"Pony", 10, 20}, {"Pod", 12, 12}};
    thing_t res[3] = {{"Poi", 1, 40}, {"Pony", 10, 20}, {"Pod", 12, 12}};

    sort_container(src, 3);

    for (int i = 0; i < 3; i++)
    {
        ck_assert_str_eq(res[i].name, src[i].name);
        ck_assert_double_eq(res[i].weight, src[i].weight);
        ck_assert_double_eq(res[i].volume, src[i].volume);
    }
}
END_TEST

// Отсортированный в обратном порядке массив
START_TEST(test_reverse_sorted)
{
    thing_t src[3] = {{"Pod", 12, 12}, {"Pony", 10, 20}, {"Poi", 1, 40}};
    thing_t res[3] = {{"Poi", 1, 40}, {"Pony", 10, 20}, {"Pod", 12, 12}};

    sort_container(src, 3);

    for (int i = 0; i < 3; i++)
    {
        ck_assert_str_eq(res[i].name, src[i].name);
        ck_assert_double_eq(res[i].weight, src[i].weight);
        ck_assert_double_eq(res[i].volume, src[i].volume);
    }
}
END_TEST

// Отсортированный в обратном порядке массив
START_TEST(test_one_element)
{
    thing_t src[1] = {{"Pod", 12, 12}};
    thing_t res[1] = {{"Pod", 12, 12}};

    sort_container(src, 1);

    for (int i = 0; i < 1; i++)
    {
        ck_assert_str_eq(res[i].name, src[i].name);
        ck_assert_double_eq(res[i].weight, src[i].weight);
        ck_assert_double_eq(res[i].volume, src[i].volume);
    }
}
END_TEST

Suite *sort_container_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sort_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_sorted);
    tcase_add_test(tc_pos, test_not_sorted);
    tcase_add_test(tc_pos, test_reverse_sorted);
    tcase_add_test(tc_pos, test_one_element);
    tcase_add_test(tc_pos, test_with_repeat);

    suite_add_tcase(s, tc_pos);

    return s;
}
