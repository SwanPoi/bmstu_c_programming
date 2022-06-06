#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "constants.h"
#include "struct.h"
#include "operations.h"
#include "search_startwith.h"
#include "sort_students.h"
#include "delete_students.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;
    FILE *src;
    
    if (argc == 3 && !strcmp(argv[1], "sb"))
    {
        src = fopen(argv[2], "rb+");
        
        if (src)
        {
            rc = sort_students(src);
            
            if (rc == ERR_OK)
            {
                rewind(src);
                rc = print_from_file(src);
            }
        }
        else
            rc = ERR_OPEN;
    }
    else if (argc == 3 && !strcmp(argv[1], "db"))
    {
        src = fopen(argv[2], "rb+");
        
        if (src)
            rc = delete_students_by_low_average(src, argv[2]);
        else
            rc = ERR_OPEN;
    }
    else if (argc == 5 && !strcmp(argv[1], "fb"))
    {
        FILE *dest = fopen(argv[3], "wb");
        src = fopen(argv[2], "rb");
        
        if (src && dest)
        {
            rc = search_startwith(src, dest, argv[4]);
            
            fclose(dest);
        }
        else
            rc = ERR_OPEN;
    }
    else
        rc = ERR_INVALID_ARGS;
        
    if (rc != ERR_OPEN && rc != ERR_INVALID_ARGS)
        fclose(src);
        
    return rc;
}
