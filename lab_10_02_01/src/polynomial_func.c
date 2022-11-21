#include <stdio.h>
#include <stdlib.h>
#include "../inc/struct.h"
#include "../inc/constants.h"
#include "../inc/polynomial_func.h"
#include "../inc/list_functions.h"

int count_polynomial(node_t *polynomial, int x)
{
    int result = 0;
    summand_t *sum = NULL;

    if (polynomial != NULL)
    {
        while (polynomial != NULL)
        {
            sum = polynomial->data;
            int cur_res = sum->multiplier;

            for (int i = 0; i < sum->degree; i++)
                cur_res *= x;

            result += cur_res;

            polynomial = polynomial->next;
        }
    }

    return result;
}

void derivative(node_t *polynomial)
{
    if (polynomial != NULL)
    {
        summand_t *sum = NULL;

        while (polynomial != NULL)
        {
            sum = polynomial->data;

            sum->multiplier *= sum->degree;
            (sum->degree)--;

            polynomial = polynomial->next;
        }
    }
}

node_t *sum_polynomials(node_t *first, node_t *second, int *rc)
{
    node_t *result = NULL;

    if (first && second)
    {
        summand_t *first_data = NULL;
        summand_t *second_data = NULL;
        node_t *cur_part = NULL;

        while (first && second && *rc == ERR_OK)
        {
            node_t *cur_node = malloc(sizeof(node_t));

            if (cur_node)
            {
                summand_t *cur_data = malloc(sizeof(summand_t));

                if (cur_data)
                {
                    first_data = first->data;
                    second_data = second->data;

                    if (first_data->degree == second_data->degree)
                    {
                        cur_data->degree = first_data->degree;
                        cur_data->multiplier = first_data->multiplier + second_data->multiplier;

                        first = first->next;
                        second = second->next;
                    }
                    else if (first_data->degree > second_data->degree)
                    {
                        cur_data->degree = first_data->degree;
                        cur_data->multiplier = first_data->multiplier;

                        first = first->next;
                    }
                    else
                    {
                        cur_data->degree = second_data->degree;
                        cur_data->multiplier = second_data->multiplier;

                        second = second->next;
                    }

                    if (cur_data->multiplier != 0)
                    {
                        cur_node->data = cur_data;
                        cur_node->next = NULL;

                        if (result == NULL)
                        {
                            result = cur_node;
                            cur_part = result;
                        }
                        else
                        {
                            cur_part->next = cur_node;
                            cur_part = cur_part->next;
                        }
                    }
                    else
                    {
                        free(cur_data);
                        free(cur_node);
                    }
                }
                else
                {
                    *rc = ERR_ALLOC;
                    free(cur_node);
                }
            }
            else
                *rc = ERR_ALLOC;
        }

        if (second != NULL && *rc == ERR_OK)
        {
            *rc = append(&cur_part, second);
        }
        else if (first != NULL && *rc == ERR_OK)
        {
            *rc = append(&cur_part, first);
        }
    }
    else
        *rc = ERR_NULL;

    return result;
}

int split_odds_and_evens(node_t *src, node_t **evens, node_t **odds)
{
    int rc = ERR_OK;

    if (src && evens && odds)
    {
        node_t *cur_even = NULL;
        node_t *cur_odd = NULL;
        summand_t *data;

        while (src && rc == ERR_OK)
        {
            data = src->data;

            node_t *cur_node = malloc(sizeof(node_t));

            if (cur_node)
            {
                summand_t *cur_data = malloc(sizeof(summand_t));

                if (cur_data)
                {
                    cur_data->degree = data->degree;
                    cur_data->multiplier = data->multiplier;

                    cur_node->data = cur_data;
                    cur_node->next = NULL;

                    if (data->degree % 2 == 0)
                    {
                        if (*evens == NULL)
                        {
                            *evens = cur_node;
                            cur_even = *evens;
                        }
                        else
                        {
                            cur_even->next = cur_node;
                            cur_even = cur_even->next;
                        }
                    }
                    else
                    {
                        if (*odds == NULL)
                        {
                            *odds = cur_node;
                            cur_odd = *odds;
                        }
                        else
                        {
                            cur_odd->next = cur_node;
                            cur_odd = cur_odd->next;
                        }
                    }

                    src = src->next;
                }
                else
                {
                    rc = ERR_ALLOC;
                    free(cur_node);
                }
            }
            else
                rc = ERR_ALLOC;
        }
    }
    else
        rc = ERR_NULL;

    return rc;
}
