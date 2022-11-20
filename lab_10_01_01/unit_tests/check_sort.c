#include <stdio.h>
#include <stdlib.h>
#include "check_sort.h"
#include "../inc/list_functions.h"
#include "../inc/struct.h"
//#include "../inc/constants.h"

// Список из одного элемента
START_TEST(test_one_film)
{
    film_t *film = malloc(sizeof(film_t));
    film->name = "Terminator";
    film->ticket_price = 1000;

    node_t *head = malloc(sizeof(node_t));

    head->next = NULL;
    head->data = film;

    node_t *res = sort(head, films_comparator);

    film_t *res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film->ticket_price);
    ck_assert_str_eq(res_film->name, film->name);

    ck_assert_ptr_null(res->next);

    free(film);
    free(head);
}
END_TEST

// Список из двух отсортированных элементов
START_TEST(test_two_sorted_films)
{
    film_t *film_1 = malloc(sizeof(film_t));
    film_1->name = "Terminator";
    film_1->ticket_price = 1000;

    film_t *film_2 = malloc(sizeof(film_t));
    film_2->name = "Snatched";
    film_2->ticket_price = 1500;

    node_t *tail = malloc(sizeof(node_t));
    tail->next = NULL;
    tail->data = film_2;

    node_t *head = malloc(sizeof(node_t));
    head->next = tail;
    head->data = film_1;

    node_t *res = sort(head, films_comparator);

    film_t *res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_str_eq(res_film->name, film_1->name);
    ck_assert_ptr_nonnull(res->next);

    res_film = res->next->data;

    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);
    ck_assert_ptr_null(res->next->next);

    (void) pop_front(&head);
    (void) pop_front(&head);

    free(film_1);
    free(film_2);
}
END_TEST

// Список из двух неотсортированных элементов
START_TEST(test_two_films)
{
    film_t *film_2 = malloc(sizeof(film_t));
    film_2->name = "Terminator";
    film_2->ticket_price = 1000;

    film_t *film_1 = malloc(sizeof(film_t));
    film_1->name = "Snatched";
    film_1->ticket_price = 1500;

    node_t *tail = malloc(sizeof(node_t));
    tail->next = NULL;
    tail->data = film_2;

    node_t *head = malloc(sizeof(node_t));
    head->next = tail;
    head->data = film_1;

    node_t *res = sort(head, films_comparator);

    film_t *res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);
    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_ptr_nonnull(res->next);

    res_film = res->next->data;

    ck_assert_str_eq(res_film->name, film_1->name);
    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_ptr_null(res->next->next);

    (void) pop_front(&head);
    (void) pop_front(&head);

    free(film_1);
    free(film_2);
}
END_TEST

// Список из двух равных элементов
START_TEST(test_two_eq_films)
{
    film_t *film_2 = malloc(sizeof(film_t));
    film_2->name = "Terminator";
    film_2->ticket_price = 1500;

    film_t *film_1 = malloc(sizeof(film_t));
    film_1->name = "Snatched";
    film_1->ticket_price = 1500;

    node_t *tail = malloc(sizeof(node_t));
    tail->next = NULL;
    tail->data = film_2;

    node_t *head = malloc(sizeof(node_t));
    head->next = tail;
    head->data = film_1;

    node_t *res = sort(head, films_comparator);

    film_t *res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_str_eq(res_film->name, film_1->name);
    ck_assert_ptr_nonnull(res->next);

    res_film = res->next->data;

    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);
    ck_assert_ptr_null(res->next->next);

    (void) pop_front(&head);
    (void) pop_front(&head);

    free(film_1);
    free(film_2);
}
END_TEST

// Список из трех элементов
START_TEST(test_three_films)
{
    film_t *film_1 = malloc(sizeof(film_t));
    film_1->name = "Terminator";
    film_1->ticket_price = 1000;

    film_t *film_2 = malloc(sizeof(film_t));
    film_2->name = "Snatched";
    film_2->ticket_price = 1500;

    film_t *film_3 = malloc(sizeof(film_t));
    film_3->name = "Angry birds";
    film_3->ticket_price = 600;

    node_t *tail = malloc(sizeof(node_t));
    tail->next = NULL;
    tail->data = film_3;

    node_t *middle = malloc(sizeof(node_t));
    middle->next = tail;
    middle->data = film_2;

    node_t *head = malloc(sizeof(node_t));
    head->next = middle;
    head->data = film_1;

    node_t *res = sort(head, films_comparator);

    film_t *res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film_3->ticket_price);
    ck_assert_str_eq(res_film->name, film_3->name);
    ck_assert_ptr_nonnull(res->next);

    res = res->next;
    
    res_film = res->data;

    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_str_eq(res_film->name, film_1->name);
    ck_assert_ptr_nonnull(res->next);

    res = res->next;
    res_film = res->data;

    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);
    ck_assert_ptr_null(res->next);

    (void) pop_front(&head);
    (void) pop_front(&head);
    (void) pop_front(&head);

    free(film_1);
    free(film_2);
    free(film_3);
}
END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sort_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_one_film);
    tcase_add_test(tc_pos, test_two_films);
    tcase_add_test(tc_pos, test_two_sorted_films);
    tcase_add_test(tc_pos, test_two_eq_films);
    tcase_add_test(tc_pos, test_three_films);

    suite_add_tcase(s, tc_pos);

    return s;
}
