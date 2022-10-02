#include <string.h>
#include "../inc/sort.h"

void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *))
{
    size_t cur_step = 1;

    char *left_border = first;
    char *right_border = (char *) first + (number - 1) * size;

    while (cur_step < number * number)
    {
        if (cur_step % 2)
            left_move_sort(&left_border, &right_border, size, comparator);
        else
            right_move_sort(&left_border, &right_border, size, comparator);

        cur_step++;
    }
}

int comp_int(const void *first_object, const void *second_object)
{
    int *left = (int *) first_object;
    int *right = (int *) second_object;

    return *left - *right;
}

void swap(void *first_object, void *second_object, size_t size)
{
    void *buf = malloc(size);

    if (buf)
    {
        memcpy(buf, first_object, size);
        memcpy(first_object, second_object, size);
        memcpy(second_object, buf, size);
    }

    free(buf);
}

void left_move_sort(char **left_border, char **right_border, size_t size, int (*comparator)(const void *, const void *))
{
    char *cur_right_border = *right_border;

    for (char *j_ptr = *left_border; j_ptr < *right_border; j_ptr += size)
    {
        if (comparator(j_ptr, j_ptr + size) > 0) {
            swap(j_ptr, (j_ptr + size), size);
            cur_right_border = j_ptr;
        }
    }
    *right_border = cur_right_border;
}

void right_move_sort(char **left_border, char **right_border, size_t size, int (*comparator)(const void *, const void *))
{
    char *cur_left_border = *left_border;

    for (char *j_ptr = *right_border; j_ptr > *left_border; j_ptr -= size)
    {
        if (comparator(j_ptr, j_ptr - size) < 0)
        {
            swap(j_ptr, (j_ptr - size), size);
            cur_left_border = j_ptr;
        }
    }
    *left_border = cur_left_border;
}
