#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "check_append.h"
#include "../inc/list_functions.h"
#include "../inc/struct.h"
#include "../inc/struct_IO.h"

// Негатив: в функцию передается NULL
START_TEST(test_null)
{
    void *res_data = pop_front(NULL);

    ck_assert_ptr_null(res_data);
}
END_TEST

// Негатив: в функцию передается указатель на NULL
START_TEST(test_ptr_null)
{
    node_t *head = NULL;

    void *res_data = pop_front(&head);

    ck_assert_ptr_null(res_data);
}
END_TEST

// Позитив: в списке один элемент
START_TEST(test_one_element)
{
    summand_t *data = malloc(sizeof(summand_t));
    data->multiplier = 5;
    data->degree = 3;

    node_t *head = malloc(sizeof(node_t));
    head->next = NULL;
    head->data = data;

    summand_t *res_data = pop_front(&head);

    ck_assert_int_eq(data->degree, res_data->degree);
    ck_assert_int_eq(data->multiplier, res_data->multiplier);
    ck_assert_ptr_null(head);

    free(res_data);
}
END_TEST

// Позитив: в списке два элемента
START_TEST(test_two_elements)
{
    summand_t *data_a = malloc(sizeof(summand_t));
    data_a->multiplier = 4;
    data_a->degree = 5;

    summand_t *data_b = malloc(sizeof(summand_t));
    data_b->multiplier = 5;
    data_b->degree = 3;

    node_t *tail = malloc(sizeof(node_t));
    tail->next = NULL;
    tail->data = data_b;

    node_t *head = malloc(sizeof(node_t));
    head->next = tail;
    head->data = data_a;

    summand_t *res_data = pop_front(&head);

    ck_assert_int_eq(data_a->degree, res_data->degree);
    ck_assert_int_eq(data_a->multiplier, res_data->multiplier);
    ck_assert_ptr_eq(head, tail);

    free(res_data);
    free_list(head);
}
END_TEST

Suite *pop_front_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("pop_front_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_one_element);
    tcase_add_test(tc_pos, test_two_elements);

    tc_neg = tcase_create("negatives");

    //Добавление негативных тестов
    tcase_add_test(tc_neg, test_null);
    tcase_add_test(tc_neg, test_ptr_null);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
