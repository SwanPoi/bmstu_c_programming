#ifndef LAB_07_SORT_H
#define LAB_07_SORT_H

#include <stdlib.h>

void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));
void left_move_sort(char **left_border, char **right_border, size_t size, int (*comparator)(const void *, const void *));
void right_move_sort(char **left_border, char **right_border, size_t size, int (*comparator)(const void *, const void *));
int comp_int(const void *fisrt_object, const void *second_object);
void swap(void *first_object, void *second_object, size_t size);

#endif //LAB_07_SORT_H
