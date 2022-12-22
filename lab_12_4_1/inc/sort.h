#ifndef LAB_07_SORT_H
#define LAB_07_SORT_H

#include <stdlib.h>

void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));
int comp_int(const void *fisrt_object, const void *second_object);

#endif //LAB_07_SORT_H
