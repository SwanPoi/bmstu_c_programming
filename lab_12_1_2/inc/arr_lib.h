#ifndef __ARR_LIB_H__
#define __ARR_LIB_H__

#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_NULL_POINTER 1
#define ERR_SMALL_ARRAY 2

int left_k_shift(int *arr, int size, int k);
int get_full_squares(int *src_array, int src_size, int *dst_array, int *dst_size);

#endif // __ARR_LIB_H__