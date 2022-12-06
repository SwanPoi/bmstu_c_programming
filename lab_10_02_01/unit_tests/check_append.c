#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "check_append.h"
#include "../inc/list_functions.h"
#include "../inc/struct.h"
#include "../inc/constants.h"
#include "../inc/struct_IO.h"

// Негатив: в функцию передаются NULL
START_TEST(test_error_ptr_null)
{
    node_t *head_b = NULL;

    int rc = append(NULL, head_b);

    ck_assert_int_eq(rc, ERR_NULL);
}
END_TEST

// Позитив: в функцию передаются указатели на NULL
START_TEST(test_both_ptr_null)
{
    node_t *head_a = NULL;
    node_t *head_b = NULL;

    int rc = append(&head_a, head_b);

    ck_assert_ptr_null(head_a);
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

// Позитив: в функцию передается второй список пуст
START_TEST(test_second_ptr_null)
{
    summand_t *data = malloc(sizeof(summand_t));
    data->multiplier = 4;
    data->degree = 5;

    node_t *head_a = malloc(sizeof(node_t));
    node_t *head_b = NULL;

    head_a->next = NULL;
    head_a->data = data;

    int rc = append(&head_a, head_b);

    summand_t *res = head_a->data;

    ck_assert_int_eq(res->degree, data->degree);
    ck_assert_int_eq(res->multiplier, data->multiplier);

    ck_assert_ptr_null(head_a->next);
    ck_assert_int_eq(rc, ERR_OK);

    free_list(head_a);
}
END_TEST

// Позитив: в функцию передается первый список пуст
START_TEST(test_first_ptr_null)
{
    summand_t *data = malloc(sizeof(summand_t));
    data->multiplier = 4;
    data->degree = 5;

    node_t *head_b = malloc(sizeof(node_t));
    node_t *head_a = NULL;

    head_b->next = NULL;
    head_b->data = data;

    int rc = append(&head_a, head_b);

    summand_t *res = head_a->data;

    ck_assert_int_eq(res->degree, data->degree);
    ck_assert_int_eq(res->multiplier, data->multiplier);

    ck_assert_ptr_null(head_a->next);
    ck_assert_int_eq(rc, ERR_OK);

    free_list(head_a);
    free_list(head_b);
}
END_TEST

// Позитив: в списках по одному элементу
START_TEST(test_two_elements)
{
    summand_t *data_a = malloc(sizeof(summand_t));
    data_a->multiplier = 4;
    data_a->degree = 5;

    summand_t *data_b = malloc(sizeof(summand_t));
    data_b->multiplier = 5;
    data_b->degree = 3;

    node_t *head_a = malloc(sizeof(node_t));
    head_a->next = NULL;
    head_a->data = data_a;

    node_t *head_b = malloc(sizeof(node_t));
    head_b->next = NULL;
    head_b->data = data_b;

    int rc = append(&head_a, head_b);

    ck_assert_int_eq(rc, ERR_OK);

    summand_t *res = head_a->data;

    ck_assert_int_eq(res->degree, data_a->degree);
    ck_assert_int_eq(res->multiplier, data_a->multiplier);

    res = head_a->next->data;

    ck_assert_int_eq(res->degree, data_b->degree);
    ck_assert_int_eq(res->multiplier, data_b->multiplier);

    free_list(head_a);
    free_list(head_b);
}
END_TEST

Suite *append_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("append_suite");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_both_ptr_null);
    tcase_add_test(tc_pos, test_first_ptr_null);
    tcase_add_test(tc_pos, test_second_ptr_null);
    tcase_add_test(tc_pos, test_two_elements);

    tcase_add_test(tc_neg, test_error_ptr_null);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
