#include <stdio.h>
#include <string.h>
#include "../inc/constants.h"
#include "../inc/IO_file.h"
#include "../inc/sort.h"
#include "../inc/filter.h"

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
            {
                int *src_array_start = calloc(count, sizeof(int));

                if (src_array_start)
                {
                    int *src_array_end = src_array_start + count;
                    read_digits_from_file(src, src_array_start, src_array_end, &rc);

                    if (rc == ERR_OK)
                    {
                        int *dst_array_start = NULL;
                        int *dst_array_end = NULL;

                        if (argc == 4)
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

                            FILE* dest = fopen(argv[2], "w");

                            if (dest)
                            {
                                write_arr_to_file(dest, dst_array_start, dst_array_end);
                                fclose(dest);
                            }
                            else
                                rc = ERR_OPEN_DEST;
                        }

                        if (argc == 4)
                        {
                            free(dst_array_start);
                            dst_array_start = NULL;
                        }
                    }
                }
                else
                    rc = ERR_SRC_MEMORY;

                free(src_array_start);
                src_array_start = NULL;
            }
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
