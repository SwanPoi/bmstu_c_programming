#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../inc/struct.h"
#include "../inc/struct_IO.h"
#include "../inc/constants.h"

// Считывание структуры из файла
int read_structure(FILE *file, thing_t *thing)
{
    int code = ERR_OK;

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
    {
        code = ERR_READ_STRING;
//        free(thing->name);
//        thing->name = NULL;
    }


    return code;
}

// Инициализация массива структур
int init_struct_array(FILE *file, thing_t **container, size_t *count_things)
{
    int code = ERR_OK;
    size_t i = 0;   
    
    while (!feof(file) && code == ERR_OK)
    {
        code = read_structure(file, (*container) + i);
        i++;

        if (code == ERR_OK && i == *count_things)
            code = realloc_container(container, i, count_things);
        else if (code != ERR_OK)
            free_container(*container, i);
    }
    
    *count_things = i;
    
    return code;
}
 
// Вывод структуры на экран
void print_structure(thing_t *thing)
{
    printf("%s", thing->name);

    printf("%lf\n%lf\n", thing->weight, thing->volume);
}

// Вывод массива структур на экран
void print_all(thing_t *container, size_t count_things)
{
    for (size_t i = 0; i < count_things; i++)
        print_structure(container + i);
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
    {
        code = ERR_REALLOC;
        free_container(*container, cur_count);
    }

    return code;
}

