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
    void *res_data = pop_back(NULL);

    ck_assert_ptr_null(res_data);
}
END_TEST

// Негатив: в функцию передается указатель на NULL
START_TEST(test_ptr_null)
{
    node_t *head = NULL;

    void *res_data = pop_back(&head);

    ck_assert_ptr_null(res_data);
}
END_TEST

// Позитив: в списке один элемент
START_TEST(test_one_film)
{
    film_t *film = malloc(sizeof(film_t));
    film->name = strdup("Terminator");
    film->ticket_price = 1000;

    node_t *head = malloc(sizeof(node_t));
    head->next = NULL;
    head->data = film;

    film_t *res_data = pop_back(&head);

    ck_assert_str_eq(film->name, res_data->name);
    ck_assert_int_eq(film->ticket_price, res_data->ticket_price);
    ck_assert_ptr_null(head);

    free_film(res_data);
}
END_TEST

// Позитив: в списке два элемента
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

    film_t *res_data = pop_back(&head);

    ck_assert_str_eq(film_2->name, res_data->name);
    ck_assert_int_eq(film_2->ticket_price, res_data->ticket_price);
    ck_assert_ptr_null(head->next);

    free_film(res_data);
    free_list(head);
}
END_TEST

Suite *pop_back_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("pop_back_suite");
    tc_pos = tcase_create("positives");

    // Добавление позитивных тестов
    tcase_add_test(tc_pos, test_one_film);
    tcase_add_test(tc_pos, test_two_films);

    tc_neg = tcase_create("negatives");

    //Добавление негативных тестов
    tcase_add_test(tc_neg, test_null);
    tcase_add_test(tc_neg, test_ptr_null);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
