#include <string.h>
#include "process.h"

size_t copy_names_startswith(thing_t *src_container, thing_t *dst_container, size_t src_count, char *substr)
{
    size_t dst_count = 0;
    
    for (size_t i = 0; i < src_count; i++)
        if (!strncmp((src_container + i)->name, substr, strlen(substr)))
        {
            dst_container[dst_count] = src_container[i];
            dst_count++;
        }
        
    return dst_count;
}

void sort_container(thing_t *container, size_t things_count)
{
    for (size_t i = 0; i < things_count - 1; i++)
        for (size_t j = i + 1; j < things_count; j++)
            if ((container + i)->weight / (container + i)->volume > (container + j)->weight / (container + j)->volume)
                swap(container + i, container + j);
}

void swap(thing_t *first, thing_t *second)
{
    thing_t tmp = *first;
    *first = *second;
    *second = tmp;
}
