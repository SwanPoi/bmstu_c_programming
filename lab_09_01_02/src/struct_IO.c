#include <string.h>
#include <stdlib.h>
#include "../inc/struct.h"
#include "../inc/struct_IO.h"
#include "../inc/constants.h"

// Считывание структуры из файла
int read_structure(FILE *file, thing_t *thing)
{
    int code = ERR_OK;

    if (!file || !thing)
        code = ERR_NULL;
    else
    {
        thing->name = NULL;
        size_t len_name = 0;

        if (!feof(file) && getline(&(thing->name), &len_name, file) != -1 && strlen(thing->name) > 1)
        {
            if (fscanf(file, "%lf", &(thing->weight)) != 1 || thing->weight < EPS)
                code = ERR_READ_WEIGHT;
            else if (fscanf(file, "%lf", &(thing->volume)) != 1 || thing->volume < EPS)
                code = ERR_READ_VOLUME;

            fscanf(file, "\n");
        }
        else
            code = ERR_READ_STRING;
    }

    return code;
}

// Инициализация массива структур
int init_struct_array(FILE *file, thing_t **container, size_t *count_things)
{
    int code = ERR_OK;
    size_t i = 0;

    if (!file || !container || !count_things)
        code = ERR_NULL;
    else
        while (!feof(file) && code == ERR_OK)
        {
            code = read_structure(file, (*container) + i);
            i++;

            if (code == ERR_OK && i == *count_things)
                code = realloc_container(container, i, count_things);
        }

    *count_things = i;

    return code;
}

// Вывод структуры на экран
int print_structure(thing_t *thing)
{
    int code = ERR_OK;

    if (!thing)
        code = ERR_NULL;
    else
    {
        printf("%s", thing->name);

        printf("%lf\n%lf\n", thing->weight, thing->volume);
    }

    return code;
}

// Вывод массива структур на экран
int print_all(thing_t *container, size_t count_things)
{
    int code = ERR_OK;

    if (!container)
        code = ERR_NULL;
    else
        for (size_t i = 0; i < count_things && code == ERR_OK; i++)
            code = print_structure(container + i);

    return code;
}

// Освобождение памяти из-под массива предметов
void free_container(thing_t *container, size_t count_things)
{
    for (size_t i = 0; i < count_things; i++)
    {
        free(container[i].name);
    }

    free(container);
}

// Перевыделение памяти под массив вещей
int realloc_container(thing_t **container, size_t cur_count, size_t *alloc_count)
{
    int code = ERR_OK;

    thing_t *buf = realloc(*container, cur_count * 2 * sizeof(thing_t));

    if (buf)
    {
        *container = buf;
        *alloc_count = cur_count * 2;
    }
    else
        code = ERR_REALLOC;

    return code;
}

