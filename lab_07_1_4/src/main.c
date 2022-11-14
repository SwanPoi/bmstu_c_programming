#include <stdio.h>
#include <string.h>
#include "../inc/constants.h"
#include "../inc/IO_file.h"
#include "../inc/task_processes.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;

    if (argc == 4 && strcmp(argv[3], "f"))
        rc = ERR_FOURTH_FLAG;
    else if (argc == 3 || argc == 4)
    {
        FILE *src = fopen(argv[1], "r");

        if (src)
        {
            int count = count_digits(src, &rc);
            rewind(src);

            if (rc == ERR_OK && count)
                rc = work_with_arrays(src, count, argc, argv[2]);
            else if (!count)
                rc = ERR_EMPTY_SRC_ARRAY;

            fclose(src);
        }
        else
            rc = ERR_OPEN_SRC;
    }
    else
        rc = ERR_COUNT_ARGS;

    return rc;
}
