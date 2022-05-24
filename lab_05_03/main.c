/*
Выбранный тип int32_t
Сортировка: Пузырьковая сортировка
Направление упорядочивания: по возрастанию
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "constants.h"
#include "operations.h"
#include "sort.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;
    FILE *file;
    
    if (argc == 4 && !strcmp(argv[1], "c") && atoi(argv[2]) > 0)
    {
        int quantity = atoi(argv[2]);
        file = fopen(argv[3], "wb");
        
        if (file)
            rc = fill_file(file, quantity);
        else
            rc = ERR_OPEN;
    }
    else if (argc == 3 && !strcmp(argv[1], "p"))
    {
        file = fopen(argv[2], "rb");
        
        if (file)
            rc = read_file(file);
        else
            rc = ERR_OPEN;
    }
    else if (argc == 3 && !strcmp(argv[1], "s"))
    {
        file = fopen(argv[2], "rb+");
        
        if (file)
            rc = sort(file);
        else
            rc = ERR_OPEN;
    }
    else
        rc = ERR_INVALID_ARGS;
        
    if (rc == ERR_OK)
        fclose(file);
        
    return rc;
}
