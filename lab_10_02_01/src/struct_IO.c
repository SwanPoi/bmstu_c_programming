#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/struct.h"
#include "../inc/struct_IO.h"
#include "../inc/constants.h"
#include "../inc/list_functions.h"

// Считывание структуры из файла
int read_structure(FILE *file, summand_t *sum)
{
    int code = ERR_OK;

    if (!file)
        code = ERR_NULL;
    else
    {
        if (fscanf(file, "%d", &(sum->multiplier)) == 1)
        {
            if (fscanf(file, "%d", &(sum->degree)) != 1 || sum->degree < 0)
                code = ERR_READ_DEGREE;
        }
        else
            code = ERR_READ_MULTIPLIAR;
    }

    return code;
}

// Вывод структуры на экран
int print_structure(FILE *file, summand_t *sum)
{
    int code = ERR_OK;

    if (!sum || !file)
        code = ERR_NULL;
    else if (sum->degree >= 0)
    {
        fprintf(file, "%d ", sum->multiplier);

        fprintf(file, "%d ", sum->degree);
    }

    return code;
}

// Вывод списка структур на экран
int print_all(FILE *file, node_t *polynomial)
{
    int code = ERR_OK;

    if (!polynomial || !file)
        code = ERR_NULL;
    else
    {
        while (polynomial != NULL && code == ERR_OK)
        {
            code = print_structure(file, polynomial->data);
            polynomial = polynomial->next;
        }

        fprintf(file, "L\n");
    }

    return code;
}

// Освобождение памяти из-под списка полинома
void free_list(node_t *polynomial)
{
    while (polynomial != NULL)
    {
        summand_t *cur_part = pop_front(&polynomial);

        free(cur_part);
    }
}

// Инициализация массива структур
int init_struct_list(FILE *file, node_t **polynomial)
{
    int code = ERR_OK;
    node_t *cur_part = NULL;
    char symb = '\0';

    if (!file)
        code = ERR_NULL;
    else
    {
        while (!feof(file) && code == ERR_OK && symb != '\n')
        {
            node_t *node = malloc(sizeof(node_t));

            if (node != NULL)
            {
                node->next = NULL;
                node->data = malloc(sizeof(summand_t));

                if (node->data != NULL)
                {
                    code = read_structure(file, node->data);

                    if (*polynomial == NULL)
                    {
                        *polynomial = node;
                        cur_part = *polynomial;
                    }
                    else
                    {
                        cur_part->next = node;
                        cur_part = cur_part->next;
                    }
                }
                else
                {
                    code = ERR_ALLOC;
                    free(node);
                }
            }
            else
                code = ERR_ALLOC;

            fscanf(file, "%c", &symb);
        }

        if (code != ERR_OK)
        {
            free_list(*polynomial);
            *polynomial = NULL;
        }
    }

    return code;
}
