#include <stdio.h>
#include "../inc/constants.h"
#include "../inc/IO_file.h"

static void write_arr_to_file(FILE *file, int *p_start, int *p_end);

int count_digits(FILE *src, int *code)
{
    int count = 0;
    int cur_digit = 0;

    while (!feof(src) && *code == ERR_OK)
        if (fscanf(src, "%d", &cur_digit) != 1)
            *code = ERR_READ_FROM_FILE_DURING_COUNT;
        else
            count++;

    return count;
}

void read_digits_from_file(FILE *src, int *p_start, int *p_end, int *code)
{
    int *p_cur = p_start;

    for (; !feof(src) && p_cur < p_end && *code == ERR_OK; p_cur++)
        if (fscanf(src, "%d", p_cur) != 1)
            *code = ERR_READ_FROM_FILE;

    if (p_cur != p_end)
        *code = ERR_LESS_DATA;
}

static void write_arr_to_file(FILE *file, int *p_start, int *p_end)
{
    for (int *p_cur = p_start; p_cur < p_end; p_cur++)
        fprintf(file, "%d ", *p_cur);
}

int write_with_validate(char *filename, int *p_start, int *p_end)
{
    int rc = ERR_OK;
    FILE* dest = fopen(filename, "w");

    if (dest)
    {
        write_arr_to_file(dest, p_start, p_end);
        fclose(dest);
    }
    else
        rc = ERR_OPEN_DEST;

    return rc;
}
