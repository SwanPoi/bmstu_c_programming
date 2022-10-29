#include <string.h>
#include <stdlib.h>
#include "../inc/process.h"
#include "../inc/constants.h"
#include "../inc/struct_IO.h"

size_t copy_names_startswith(thing_t *src_container, thing_t *dst_container, size_t src_count, char *substr)
{
    size_t dst_count = 0;
    
    for (size_t i = 0; i < src_count; i++)
        if (!strncmp((src_container + i)->name, substr, strlen(substr)))
        {
            dst_container[dst_count].name = strdup(src_container[i].name);
            dst_container[dst_count].volume = src_container[i].volume;
            dst_container[dst_count].weight = src_container[i].weight;

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

int prefix_process(thing_t *container, size_t count_things, char *prefix)
{
    int code = ERR_OK;

    thing_t *prefix_container = calloc(count_things, sizeof(thing_t));

    if (prefix_container)
    {
        size_t prefix_count = copy_names_startswith(container, prefix_container, count_things, prefix);

        if (prefix_count)
            print_all(prefix_container, prefix_count);
        else
            code = ERR_NO_DATA;

        free_container(prefix_container, prefix_count);
    }
    else
        code = ERR_ALLOC_PREFIX;

    return code;
}
