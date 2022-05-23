#include <stdio.h>
#include "process.h"

int process(FILE *f, size_t *index)
{
    int rc = ERR_OK;
    int cur_element;
    if (fscanf(f, "%d", &cur_element) == 1)
    {
        *index = 1;
        int cur_index = 1;
        int max_element = cur_element;
        
        while (fscanf(f, "%d", &cur_element))
        {
            cur_index++;
            
            if (cur_element > max_element)
            {
                max_element = cur_element;
                *index = cur_index;
            }
        }
    }
    else
        rc = ERR_EMPTY;
    
    return rc;
}

