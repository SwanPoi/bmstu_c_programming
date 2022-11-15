#include <stdlib.h>
#include <stdio.h>
#include "../inc/sort.h"
#include "../inc/filter.h"
#include "../inc/IO_file.h"
#include "../inc/constants.h"
#include "../inc/task_processes.h"

int new_array_process(int *src_array_start, int *src_array_end, char *filename, int count_args)
{
    int rc = ERR_OK;

    int *dst_array_start = NULL;
    int *dst_array_end = NULL;

    if (count_args == 4)
    {
        rc = key((const int *) src_array_start, (const int *) src_array_end, &dst_array_start, &dst_array_end);
    }
    else
    {
        dst_array_start = src_array_start;
        dst_array_end = src_array_end;
    }

    if (rc == ERR_OK)
    {
        mysort(dst_array_start, dst_array_end - dst_array_start, sizeof(int), comp_int);

        rc = write_with_validate(filename, dst_array_start, dst_array_end);
    }

    if (count_args == 4)
    {
        free(dst_array_start);
        dst_array_start = NULL;
    }

    return rc;
}

int work_with_arrays(FILE *src, int count_digits, int count_args, char *dst_name)
{
    int rc = ERR_OK;

    int *src_array_start = calloc(count_digits, sizeof(int));

    if (src_array_start)
    {
        int *src_array_end = src_array_start + count_digits;
        read_digits_from_file(src, src_array_start, src_array_end, &rc);

        if (rc == ERR_OK)
            rc = new_array_process(src_array_start, src_array_end, dst_name, count_args);
    }
    else
        rc = ERR_SRC_MEMORY;

    free(src_array_start);
    src_array_start = NULL;

    return rc;
}
