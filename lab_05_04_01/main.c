#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "constants_and_struct.h"
#include "read_write_structure.h"
#include "search_sort_del.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;
    int opened = HERE;
    FILE *src;
    
    if (argc == 3 && !strcmp(argv[1], "st"))
    {
        rc = sort_in_file(argv[2]);
        
        opened = NOT_HERE;
    }
    else if (argc == 3 && !strcmp(argv[1], "dt"))
    {
        rc = delete_from_file(argv[2]);
        opened = NOT_HERE;
    }
    else if (argc == 5 && !strcmp(argv[1], "ft"))
    {
        FILE *dest = fopen(argv[3], "w");
        src = fopen(argv[2], "r");
        
        if (src && dest)
        {
            rc = search_and_write(src, dest, argv[4]);
            
            fclose(dest);
        }
        else
            rc = ERR_OPEN;
    }
    else
        rc = ERR_INVALID_ARGS;
        
    if (opened == HERE && rc != ERR_OPEN && rc != ERR_INVALID_ARGS)
        fclose(src);
        
    return rc;
}
