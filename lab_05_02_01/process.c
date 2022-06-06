#include <stdio.h>
#include "constants.h"
#include "process.h"

int more_than_avrg_of_max_and_min(FILE *file, int *code)
{
    int count = -1;
    double max, min;
    
    get_max_and_min(file, &max, &min, code);
    
    if (*code == ERR_OK)
    {
        double average = (max + min) / 2;
        
        rewind(file);
        
        count = count_more_than(file, average);
    }
    
    return count;
}

void get_max_and_min(FILE *file, double *max, double *min, int *code)
{
    double cur_element = 0;
    
    if (fscanf(file, "%lf", &cur_element) == 1)
    {
        *max = cur_element;
        *min = cur_element;
        
        while (!feof(file) && *code == ERR_OK)
            if (fscanf(file, "%lf", &cur_element) != 1 && !feof(file))
                *code = ERR_INPUT;
            else if (cur_element > *max)
                *max = cur_element;
            else if (cur_element < *min)
                *min = cur_element;
    }
    else
        *code = ERR_NO_DATA;
}

int count_more_than(FILE *file, double to_compare)
{
    int count = 0;
    double cur_element;
    
    while (fscanf(file, "%lf", &cur_element) == 1)
        if (cur_element > to_compare)
            count++;
    
    return count;
}
