#include <stdio.h>
#include "constants.h"
#include "process.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;
    
    if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
       
        if (file)
        {
            int count_necessary = more_than_avrg_of_max_and_min(file, &rc);
           
            if (rc == ERR_OK)
                printf("Count of necessary: %d\n", count_necessary);
           
            fclose(file);
        }
        else
            rc = ERR_OPEN;
    }
    else
        rc = ERR_NO_ARGS;
    
    return rc;
}
