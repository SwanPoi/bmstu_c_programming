#include <stdlib.h>
#include "../inc/filter.h"
#include "../inc/constants.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    int code = ERR_OK;

    if (!pb_src || !pe_src)
        code = ERR_NULL_POINTER;
    else if (pe_src <= pb_src)
        code = ERR_END_LESS_START;
    else
    {
        double mean = arithmetic_mean(pb_src, pe_src);

        int count_more_than_mean = count_more_than_mean_elements(pb_src, pe_src, mean);

        if (!count_more_than_mean)
            code = ERR_EMPTY_FILTER_ARRAY;
        else
        {
            *pb_dst = calloc(count_more_than_mean, sizeof(int));

            if (*pb_dst)
            {
                *pe_dst = *pb_dst + count_more_than_mean;

                copy_more_than_mean_elements(pb_src, pe_src, *pb_dst, mean);
            }
            else
                code = ERR_PB_DST;
        }
    }

    return code;
}

double arithmetic_mean(const int *p_begin, const int *p_end)
{
    int sum = 0;

    for (int *cur_p = (int *) p_begin; cur_p < (int *) p_end; cur_p++)
        sum += *cur_p;

    return sum / (p_end - p_begin);
}

int count_more_than_mean_elements(const int *p_begin, const int *p_end, double mean)
{
    int count = 0;

    for (int *cur_p = (int *) p_begin; cur_p < (int *) p_end; cur_p++)
        if (*cur_p > mean)
            count++;

    return count;
}

void copy_more_than_mean_elements(const int *pb_src, const int *pe_src, int *pb_dst, double mean)
{
    int *cur_dst = pb_dst;

    for (int *cur_src = (int *) pb_src; cur_src < (int *) pe_src; cur_src++)
        if (*cur_src > mean)
        {
            *cur_dst = *cur_src;
            cur_dst++;
        }
}
