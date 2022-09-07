#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"
#include "struct_IO.h"
#include "constants.h"

// Считывание структуры из файла
int read_structure(FILE *file, thing_t *thing)
{
    int code = ERR_OK;
    
    if (!feof(file) && fgets(thing->name, STRING_LENGTH + 2, file) != NULL && strlen(thing->name) > 1)
    {
        if (fscanf(file, "%lf", &(thing->weight)) != 1 || thing->weight < EPS)
            code = ERR_READ_WEIGHT;
        else if (fscanf(file, "%lf", &(thing->volume)) != 1 || thing->volume < EPS)
            code = ERR_READ_VOLUME;
        
        fscanf(file, "\n");
    }
    else
        code = ERR_READ_STRING;
    
    return code;
}

// Инициализация массива структур
int init_struct_array(FILE *file, thing_t *container, size_t *count_things)
{
    int code = ERR_OK;
    size_t i = 0;   
    
    while (!feof(file) && code == ERR_OK)
    {
        code = read_structure(file, container + i);
        i++;
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
