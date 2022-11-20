#include <string.h>
#include <stdlib.h>
#include "../inc/struct.h"
#include "../inc/struct_IO.h"
#include "../inc/constants.h"
#include "../inc/list_functions.h"

// Считывание структуры из файла
int read_structure(FILE *file, film_t *film)
{
    int code = ERR_OK;

    if (!file)
        code = ERR_NULL;
    else
    {
        film->name = NULL;
        size_t len_name = 0;

        if (!feof(file) && getline(&(film->name), &len_name, file) != -1 && strlen(film->name) > 1)
        {
            if (fscanf(file, "%d", &(film->ticket_price)) != 1 || film->ticket_price < 0)
                code = ERR_READ_PRICE;

            fscanf(file, "\n");
        }
        else
            code = ERR_READ_STRING;
    }

    return code;
}

// Вывод структуры на экран
int print_structure(FILE *file, film_t *film)
{
    int code = ERR_OK;

    if (!film || !file)
        code = ERR_NULL;
    else
    {
        fprintf(file, "%s", film->name);

        fprintf(file, "%d\n", film->ticket_price);
    }

    return code;
}

// Вывод списка структур на экран
int print_all(FILE *file, node_t *films)
{
    int code = ERR_OK;

    if (!films || !file)
        code = ERR_NULL;
    else
        while (films != NULL && code == ERR_OK)
        {
            code = print_structure(file, films->data);
            films = films->next;
        }

    return code;
}

// Освобождение памяти из-под списка фильмов
void free_list(node_t *films)
{
    while (films != NULL)
    {
        film_t *cur_film = pop_front(&films);

        free_film(cur_film);
    }
}

void free_film(film_t *film)
{
    free(film->name);
    free(film);
}

// Инициализация массива структур
int init_struct_list(FILE *file, node_t **films)
{
    int code = ERR_OK;
    node_t *cur_film = NULL;

    if (!file)
        code = ERR_NULL;
    else
        while (!feof(file) && code == ERR_OK)
        {
            node_t *node = malloc(sizeof(node_t));

            if (node != NULL)
            {
                node->next = NULL;
                node->data = malloc(sizeof(film_t));

                if (node->data != NULL)
                {
                    code = read_structure(file, node->data);

                    if (code == ERR_OK)
                    {
                        if (*films == NULL)
                        {
                            *films = node;
                            cur_film = *films;
                        }
                        else
                        {
                            cur_film->next = node;
                            cur_film = cur_film->next;
                        }    
                    }
                }
                else
                    code = ERR_ALLOC;
            }
            else
                code = ERR_ALLOC;
        }

    return code;
}