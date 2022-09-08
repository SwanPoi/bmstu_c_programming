#include <stdio.h>
#include <string.h>
#include "struct_IO.h"
#include "process.h"
#include "constants.h"
#include "struct.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;
    FILE *file;
    
    if (argc == 2 || argc == 3)
    {
        file = fopen(argv[1], "r");
        
        if (file)
        {
            thing_t container[MAX_N];
            size_t count_things = 0;
            
            rc = init_struct_array(file, container, &count_things);
            
            if (rc == ERR_OK)
            {
                if (argc == 2)
                {
                    sort_container(container, count_things);
                    print_all(container, count_things);
                }
                else if (argc == 3 && !strcmp(argv[2], DEFAULT_PREFIX))
                    print_all(container, count_things);
                else
                {
                    thing_t prefix_container[MAX_N];
                    
                    size_t prefix_count = copy_names_startswith(container, prefix_container, count_things, argv[2]);
                    
                    if (prefix_count)
                        print_all(prefix_container, prefix_count);
                    else
                        rc = ERR_NO_DATA;
                }
            }
            
            fclose(file);
        }
        else
            rc = ERR_OPEN;
    }
    else
        rc = ERR_INVALID_ARGS;
    
    return rc;
}
