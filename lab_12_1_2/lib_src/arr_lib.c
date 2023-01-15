#include "../inc/arr_lib.h"

static int is_full_square(int digit);

// Циклический сдвиг массива на k позиций влево
int left_k_shift(int *arr, int size, int k)
{
    int rc = ERR_OK;

    if (arr == NULL)
        rc = ERR_NULL_POINTER;
    else
        for (int index = 0; index < k; index++)
        {
            int cur = arr[0];

            for (int i = 0; i < size - 1; i++)
                arr[i] = arr[i + 1];

            arr[size - 1] = cur;
        }

    return rc;
}

// Функция, помещающая в новый массив полные квадраты
int get_full_squares(int *src_array, int src_size, int *dst_array, int *dst_size)
{
    int rc = ERR_OK;

    if (src_array == NULL || dst_size == NULL)
        rc = ERR_NULL_POINTER;
    else
    {
        int new_size = 0;

        for (int i = 0; i < src_size; i++)
            if (is_full_square(src_array[i]) == 1)
                new_size++;

        if (dst_array == NULL)
            *dst_size = new_size;
        else if (*dst_size < new_size)
            rc = ERR_SMALL_ARRAY;
        else
        {
            new_size = 0;

            for (int i = 0; i < src_size; i++)
                if (is_full_square(src_array[i]) == 1)
                    dst_array[new_size++] = src_array[i];
        }
    }

    return rc;
}

// Определение, является ли число полным квадратом
static int is_full_square(int digit)
{
    int is_square = 0;

    if (digit > 0 && pow(ceil(sqrt(digit)), 2) == digit)
        is_square = 1;

    return is_square;
}