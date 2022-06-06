#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include "operations.h"
#include "sort.h"

int_type get_number_by_pos(FILE *file, int position, int *code)
{
    int_type number_in_pos = 0;
    long int start_pos = ftell(file);
    
    if (fseek(file, position, SEEK_SET) || fread(&number_in_pos, SIZE, 1, file) != 1)
        *code = ERR_INVALID_POS;
    else
        fseek(file, start_pos, SEEK_SET);
    
    return number_in_pos;
}

int put_number_by_pos(FILE *file, int position, int_type number)
{
    int code = ERR_OK;
    long int start_pos = ftell(file);
    
    if (fseek(file, position, SEEK_SET))
        code = ERR_INVALID_POS;
    else if (fwrite(&number, SIZE, 1, file) != 1)
        code = ERR_WRITE;
    else
        fseek(file, start_pos, SEEK_SET);
    
    return code;
}

int swap(FILE *file, int left_pos, int right_pos)
{
    int code = ERR_OK;
    
    int_type val_left = get_number_by_pos(file, left_pos, &code);
    if (code == ERR_OK)
    {
        int_type val_right = get_number_by_pos(file, right_pos, &code);
        
        if (code == ERR_OK)
        {
            code = put_number_by_pos(file, left_pos, val_right);
            
            if (code == ERR_OK)
                code = put_number_by_pos(file, right_pos, val_left);
        }
    }
    
    return code;
}

int sort(FILE *file)
{
    int code = check_correct_file(file);
    
    if (code == ERR_OK)
    {
        fseek(file, 0, SEEK_END);
        
        int quantity = ftell(file) / SIZE;
        
        rewind(file);
        
        int is_sorted = FALSE;
        
        for (int i = 0; i < quantity - 1 && is_sorted == FALSE && code == ERR_OK; i++)
        {
            is_sorted = TRUE;
            
            for (int j = 0; j < quantity - i - 1 && code == ERR_OK; j++)
            {
                int_type val_left = get_number_by_pos(file, j * SIZE, &code);
                int_type val_right = get_number_by_pos(file, (j + 1) * SIZE, &code);
                
                if (code == ERR_OK)
                    if (val_left > val_right)
                    {
                        code = swap(file, j * SIZE, (j + 1) * SIZE);
                        is_sorted = FALSE;
                    }
            }
        }
    }
    
    return code;
}
