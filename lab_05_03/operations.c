#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include "operations.h"
#include "constants.h"

int fill_file(FILE *file, int quantity)
{
    int code = ERR_OK;
    
    srand(time(NULL));
    
    for (int i = 0; i < quantity && code == ERR_OK; i++)
    {
        int32_t cur_number = (int_type) rand() % MAX_NUMBER;
        
        if (fwrite(&cur_number, SIZE, 1, file) != 1)
            code = ERR_WRITE;
    }
    
    return code;
}

int read_file(FILE *file)
{
    int code = check_correct_file(file);
    
    if (code == ERR_OK)
    {
        int_type cur_number;
        
        if (fread(&cur_number, SIZE, 1, file) == 1)
        {
            printf("%d ", cur_number);
            
            while (fread(&cur_number, SIZE, 1, file) == 1)
                printf("%d ", cur_number);
            
            printf("\n");
        }
        else
            code = ERR_INVALID_IN;
    }
    
    return code;
}

int check_correct_file(FILE *file)
{
    int code = ERR_OK;
    
    if (fseek(file, 0, SEEK_END) || ftell(file) == -1L)
        code = ERR_READ;
    else if (ftell(file) % SIZE != 0)
        code = ERR_INVALID_CONTENT;
    
    rewind(file);
    
    return code;    
}
