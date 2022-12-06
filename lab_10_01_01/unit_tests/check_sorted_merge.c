#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "check_append.h"
#include "../inc/list_functions.h"
#include "../inc/struct.h"
#include "../inc/struct_IO.h"

// Второй указатель - null
START_TEST(test_second_null_film)
{
    film_t *film = malloc(sizeof(film_t));
    film->name = strdup("Terminator");
    film->ticket_price = 1000;

    node_t *head = malloc(sizeof(node_t));

    head->next = NULL;
    head->data = film;

    node_t *back = NULL;

    node_t *res = sorted_merge(&head, &back,films_comparator);

    film_t *res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film->ticket_price);
    ck_assert_str_eq(res_film->name, film->name);

    ck_assert_ptr_null(res->next);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(back);

    free_list(res);
}
END_TEST

// Первый указатель - null
START_TEST(test_first_null_film)
{
    film_t *film = malloc(sizeof(film_t));
    film->name = strdup("Terminator");
    film->ticket_price = 1000;

    node_t *back = malloc(sizeof(node_t));

    back->next = NULL;
    back->data = film;

    node_t *head = NULL;

    node_t *res = sorted_merge(&head, &back,films_comparator);

    film_t *res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film->ticket_price);
    ck_assert_str_eq(res_film->name, film->name);

    ck_assert_ptr_null(res->next);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(back);

    free_list(res);
}
END_TEST

// Оба указателя - null
START_TEST(test_both_null_film)
{
    node_t *back = NULL;

    node_t *head = NULL;

    node_t *res = sorted_merge(&head, &back,films_comparator);

    ck_assert_ptr_null(res);
    ck_assert_ptr_null(head);
    ck_assert_ptr_null(back);
}
END_TEST

// Список из двух отсортированных элементов
START_TEST(test_two_sorted_films)
{
    film_t *film_1 = malloc(sizeof(film_t));
    film_1->name = strdup("Terminator");
    film_1->ticket_price = 1000;

    film_t *film_2 = malloc(sizeof(film_t));
    film_2->name = strdup("Snatched");
    film_2->ticket_price = 1500;

    node_t *tail = malloc(sizeof(node_t));
    tail->next = NULL;
    tail->data = film_2;

    node_t *head = malloc(sizeof(node_t));
    head->next = NULL;
    head->data = film_1;

    node_t *res = sorted_merge(&head, &tail, films_comparator);

    film_t *res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_str_eq(res_film->name, film_1->name);
    ck_assert_ptr_nonnull(res->next);

    res_film = res->next->data;

    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);
    ck_assert_ptr_null(res->next->next);

    ck_assert_ptr_null(head);
    ck_assert_ptr_null(tail);

    free_list(res);
}
END_TEST

// Список из двух неотсортированных элементов
START_TEST(test_two_films)
{
    film_t *film_2 = malloc(sizeof(film_t));
    film_2->name = strdup("Terminator");
    film_2->ticket_price = 1000;

    film_t *film_1 = malloc(sizeof(film_t));
    film_1->name = strdup("Snatched");
    film_1->ticket_price = 1500;

    node_t *tail = malloc(sizeof(node_t));
    tail->next = NULL;
    tail->data = film_2;

    node_t *head = malloc(sizeof(node_t));
    head->next = NULL;
    head->data = film_1;

    node_t *res = sorted_merge(&head, &tail, films_comparator);

    film_t *res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);
    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_ptr_nonnull(res->next);

    res_film = res->next->data;

    ck_assert_str_eq(res_film->name, film_1->name);
    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_ptr_null(res->next->next);

    ck_assert_ptr_null(head);
    ck_assert_ptr_null(tail);

    free_list(res);
}
END_TEST

// Список из двух равных элементов
START_TEST(test_two_eq_films)
{
    film_t *film_2 = malloc(sizeof(film_t));
    film_2->name = strdup("Terminator");
    film_2->ticket_price = 1500;

    film_t *film_1 = malloc(sizeof(film_t));
    film_1->name = strdup("Snatched");
    film_1->ticket_price = 1500;

    node_t *tail = malloc(sizeof(node_t));
    tail->next = NULL;
    tail->data = film_2;

    node_t *head = malloc(sizeof(node_t));
    head->next = NULL;
    head->data = film_1;

    node_t *res = sorted_merge(&head, &tail, films_comparator);

    film_t *res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_str_eq(res_film->name, film_1->name);
    ck_assert_ptr_nonnull(res->next);

    res_film = res->next->data;

    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);
    ck_assert_ptr_null(res->next->next);

    ck_assert_ptr_null(head);
    ck_assert_ptr_null(tail);

    free_list(res);
}
END_TEST

// Список из трех элементов
START_TEST(test_three_films)
{
    film_t *film_1 = malloc(sizeof(film_t));
    film_1->name = strdup("Terminator");
    film_1->ticket_price = 1000;

    film_t *film_2 = malloc(sizeof(film_t));
    film_2->name = strdup("Snatched");
    film_2->ticket_price = 1500;

    film_t *film_3 = malloc(sizeof(film_t));
    film_3->name = strdup("Angry birds");
    film_3->ticket_price = 600;

    node_t *tail = malloc(sizeof(node_t));
    tail->next = NULL;
    tail->data = film_3;

    node_t *middle = malloc(sizeof(node_t));
    middle->next = NULL;
    middle->data = film_2;

    node_t *head = malloc(sizeof(node_t));
    head->next = middle;
    head->data = film_1;

    node_t *res = sorted_merge(&head, &tail, films_comparator);
    node_t *cur_res = res;

    film_t *res_film = cur_res->data;

    ck_assert_int_eq(res_film->ticket_price, film_3->ticket_price);
    ck_assert_str_eq(res_film->name, film_3->name);
    ck_assert_ptr_nonnull(cur_res->next);

    cur_res = cur_res->next;
    
    res_film = cur_res->data;

    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_str_eq(res_film->name, film_1->name);
    ck_assert_ptr_nonnull(cur_res->next);

    cur_res = cur_res->next;
    res_film = cur_res->data;

    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);
    ck_assert_ptr_null(cur_res->next);

    ck_assert_ptr_null(head);
    ck_assert_ptr_null(tail);

    free_list(res);
}
END_TEST

Suite *sorted_merge_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sorted_merge_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_second_null_film);
    tcase_add_test(tc_pos, test_first_null_film);
    tcase_add_test(tc_pos, test_both_null_film);
    tcase_add_test(tc_pos, test_two_films);
    tcase_add_test(tc_pos, test_two_sorted_films);
    tcase_add_test(tc_pos, test_two_eq_films);
    tcase_add_test(tc_pos, test_three_films);

    suite_add_tcase(s, tc_pos);

    return s;
}
