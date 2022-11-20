#include <stdio.h>
#include <stdlib.h>
#include "check_append.h"
#include "../inc/list_functions.h"
#include "../inc/struct.h"
//#include "../inc/constants.h"

// Позитив: в функцию передаются указатели на NULL
START_TEST(test_both_ptr_null)
{
    node_t *head_a = NULL;
    node_t *head_b = NULL;

    append(&head_a, &head_b);

    ck_assert_ptr_null(head_a);
    ck_assert_ptr_null(head_b);
}
END_TEST

// Позитив: в функцию передается второй указатель на NULL
START_TEST(test_second_ptr_null)
{
    film_t *film = malloc(sizeof(film_t));
    film->name = "Terminator";
    film->ticket_price = 1000;

    node_t *head_a = malloc(sizeof(node_t));
    node_t *head_b = NULL;

    head_a->next = NULL;
    head_a->data = film;

    append(&head_a, &head_b);

    film_t *res_film = head_a->data;

    ck_assert_int_eq(res_film->ticket_price, film->ticket_price);
    ck_assert_str_eq(res_film->name, film->name);

    ck_assert_ptr_null(head_a->next);
    ck_assert_ptr_null(head_b);

    free(film);
    free(head_a);
}
END_TEST

// Позитив: в функцию передается первый указатель на NULL
START_TEST(test_first_ptr_null)
{
    film_t *film = malloc(sizeof(film_t));
    film->name = "Terminator";
    film->ticket_price = 1000;

    node_t *head_b = malloc(sizeof(node_t));
    node_t *head_a = NULL;

    head_b->next = NULL;
    head_b->data = film;

    append(&head_a, &head_b);

    film_t *res_film = head_a->data;

    ck_assert_int_eq(res_film->ticket_price, film->ticket_price);
    ck_assert_str_eq(res_film->name, film->name);

    ck_assert_ptr_null(head_a->next);
    ck_assert_ptr_null(head_b);

    free(film);
    free(head_a);
}
END_TEST

// Позитив: в списках по одному элементу
START_TEST(test_two_films)
{
    film_t *film_1 = malloc(sizeof(film_t));
    film_1->name = "Terminator";
    film_1->ticket_price = 1000;

    film_t *film_2 = malloc(sizeof(film_t));
    film_2->name = "Snatched";
    film_2->ticket_price = 1500;

    node_t *head_a = malloc(sizeof(node_t));
    head_a->next = NULL;
    head_a->data = film_1;

    node_t *head_b = malloc(sizeof(node_t));
    head_b->next = NULL;
    head_b->data = film_2;

    append(&head_a, &head_b);

    ck_assert_ptr_null(head_b);

    film_t *res_film = head_a->data;

    ck_assert_int_eq(res_film->ticket_price, film_1->ticket_price);
    ck_assert_str_eq(res_film->name, film_1->name);

    res_film = head_a->next->data;

    ck_assert_str_eq(res_film->name, film_2->name);
    ck_assert_int_eq(res_film->ticket_price, film_2->ticket_price);

    (void) pop_front(&head_a);
    (void) pop_front(&head_a);

    free(film_1);
    free(film_2);
}
END_TEST

Suite *append_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("append_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_both_ptr_null);
    tcase_add_test(tc_pos, test_first_ptr_null);
    tcase_add_test(tc_pos, test_second_ptr_null);
    tcase_add_test(tc_pos, test_two_films);

    suite_add_tcase(s, tc_pos);

    return s;
}
