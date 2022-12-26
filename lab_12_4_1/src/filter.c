#include <stdlib.h>
#include <stdio.h>
#include "../inc/filter.h"
#include "../inc/constants.h"

static int count_more_than_mean_elements(const int *p_begin, const int *p_end, double mean);
static double arithmetic_mean(const int *p_begin, const int *p_end);
static void copy_more_than_mean_elements(const int *pb_src, const int *pe_src, int *pb_dst, double mean);

int key(const int *pb_src, const int *pe_src, int *pb_dst, int *count_more_than_mean)
{
    int code = ERR_OK;

    if (!pb_src || !pe_src || !count_more_than_mean)
        code = ERR_NULL_POINTER;
    else if (pe_src <= pb_src)
        code = ERR_END_LESS_START;
    else
    {
        double mean = arithmetic_mean(pb_src, pe_src);

        *count_more_than_mean = count_more_than_mean_elements(pb_src, pe_src, mean);

        if ((*count_more_than_mean) == 0)
            code = ERR_EMPTY_FILTER_ARRAY;
        else if (pb_dst != NULL)
        {
            copy_more_than_mean_elements(pb_src, pe_src, pb_dst, mean);
        }
    }

    return code;
}

static double arithmetic_mean(const int *p_begin, const int *p_end)
{
    int sum = 0;

    for (int *cur_p = (int *) p_begin; cur_p < (int *) p_end; cur_p++)
        sum += *cur_p;

    return (double) sum / (p_end - p_begin);
}

static int count_more_than_mean_elements(const int *p_begin, const int *p_end, double mean)
{
    int count = 0;

    for (int *cur_p = (int *) p_begin; cur_p < (int *) p_end; cur_p++)
        if (*cur_p > mean)
            count++;

    return count;
}

static void copy_more_than_mean_elements(const int *pb_src, const int *pe_src, int *pb_dst, double mean)
{
    int *cur_dst = pb_dst;

    for (int *cur_src = (int *) pb_src; cur_src < (int *) pe_src; cur_src++)
        if (*cur_src > mean)
        {
            *cur_dst = *cur_src;
            cur_dst++;
        }
}
