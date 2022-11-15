#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/struct_IO.h"
#include "../inc/process.h"
#include "../inc/constants.h"
#include "../inc/struct.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;
    FILE *file;
    
    if (argc == 2 || argc == 3)
    {
        file = fopen(argv[1], "r");
        
        if (file)
        {
            thing_t *container = calloc(MAX_N, sizeof(thing_t));

            if (container)
            {
                size_t count_things = MAX_N;

                rc = init_struct_array(file, &container, &count_things);

                fclose(file);

                if (rc == ERR_OK)
                {
                    if (argc == 2)
                    {
                        rc = sort_container(container, count_things);
                        
                        if (rc == ERR_OK)
                            rc = print_all(container, count_things);
                    }
                    else if (argc == 3 && !strcmp(argv[2], DEFAULT_PREFIX))
                        rc = print_all(container, count_things);
                    else
                        rc = prefix_process(container, count_things, argv[2]);
                }

                free_container(container, count_things);
            }
            else
                rc = ERR_ALLOC;
        }
        else
            rc = ERR_OPEN;
    }
    else
        rc = ERR_INVALID_ARGS;
    
    return rc;
}
