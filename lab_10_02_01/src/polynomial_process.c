#include <stdio.h>
#include <stdlib.h>
#include "../inc/struct.h"
#include "../inc/struct_IO.h"
#include "../inc/polynomial_func.h"
#include "../inc/polynomial_process.h"
#include "../inc/constants.h"

int ddx_process(void)
{
    int rc = ERR_OK;

    node_t *polynomial = NULL;

    rc = init_struct_list(stdin, &polynomial);

    if (rc == ERR_OK)
    {
        derivative(polynomial);

        print_all(stdout, polynomial);

        free_list(polynomial);
    }

    return rc;
}

int val_process(void)
{
    int rc = ERR_OK;

    node_t *polynomial = NULL;

    rc = init_struct_list(stdin, &polynomial);

    if (rc == ERR_OK)
    {
        int x = 0;

        if (scanf("%d", &x) == 1)
        {
            int result = count_polynomial(polynomial, x);

            printf("%d\n", result);
        }
        else
            rc = ERR_READ_ARG;
    }

    free_list(polynomial);

    return rc;
}

int sum_process(void)
{
    int rc = ERR_OK;

    node_t *first_polynomial = NULL;

    rc = init_struct_list(stdin, &first_polynomial);

    if (rc == ERR_OK)
    {
        node_t *second_polynomial = NULL;

        rc = init_struct_list(stdin, &second_polynomial);

        if (rc == ERR_OK)
        {
            node_t *result = sum_polynomials(first_polynomial, second_polynomial, &rc);

            if (rc == ERR_OK)
            {
                print_all(stdout, result);
                free_list(result);
            }

            free_list(second_polynomial);
        }

        free_list(first_polynomial);
    }

    return rc;
}

int dvd_process(void)
{
    int rc = ERR_OK;

    node_t *src_polynomial = NULL;

    rc = init_struct_list(stdin, &src_polynomial);

    if (rc == ERR_OK)
    {
        node_t *evens = NULL;
        node_t *odds = NULL;

        rc = split_odds_and_evens(src_polynomial, &evens, &odds);

        if (rc == ERR_OK)
        {
            print_all(stdout, evens);
            print_all(stdout, odds);

            free_list(evens);
            free_list(odds);
        }

        free_list(src_polynomial);
    }

    return rc;
}
