#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "check_append.h"
#include "../inc/list_functions.h"
#include "../inc/struct.h"
#include "../inc/struct_IO.h"

// Список из одного элемента
START_TEST(test_one_film)
{
    film_t *film = malloc(sizeof(film_t));
    film->name = strdup("Terminator");
    film->ticket_price = 1000;

    node_t *head = malloc(sizeof(node_t));
    node_t *back = NULL;

    head->next = NULL;
    head->data = film;

    front_back_split(head, &back);

    film_t *res_film = head->data;

    ck_assert_int_eq(res_film->ticket_price, film->ticket_price);
    ck_assert_str_eq(res_film->name, film->name);

    ck_assert_ptr_null(head->next);
    ck_assert_ptr_null(back);

    free_list(head);
}
END_TEST

// Список из двух элементов
START_TEST(test_two_films)
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
    head->next = tail;
    head->data = film_1;

    node_t *back = NULL;

    front_back_split(head, &back);

    film_t *res_film = head->data;

    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_str_eq(res_film->name, film_1->name);
    ck_assert_ptr_null(head->next);

    res_film = back->data;

    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);
    ck_assert_ptr_null(back->next);

    free_list(head);
    free_list(back);
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
    middle->next = tail;
    middle->data = film_2;

    node_t *head = malloc(sizeof(node_t));
    head->next = middle;
    head->data = film_1;

    node_t *back = NULL;

    front_back_split(head, &back);

    film_t *res_film = head->data;

    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_str_eq(res_film->name, film_1->name);
    ck_assert_ptr_nonnull(head->next);
    
    res_film = head->next->data;

    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);
    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_ptr_null(head->next->next);

    res_film = back->data;

    ck_assert_str_eq(res_film->name, film_3->name);
    ck_assert_int_eq(res_film->ticket_price, film_3->ticket_price);
    ck_assert_ptr_null(back->next);

    free_list(head);
    free_list(back);
}
END_TEST

Suite *front_back_split_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("front_back_split_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_one_film);
    tcase_add_test(tc_pos, test_two_films);
    tcase_add_test(tc_pos, test_three_films);

    suite_add_tcase(s, tc_pos);

    return s;
}
