#include <string.h>
#include <stdlib.h>
#include "../inc/process.h"
#include "../inc/constants.h"
#include "../inc/struct_IO.h"

int copy_names_startswith(thing_t *src_container, thing_t *dst_container, size_t src_count, size_t *dst_count, char *substr)
{
    int code = ERR_OK;

    if (!src_container || !dst_container || !dst_count)
        code = ERR_NULL;
    else
        for (size_t i = 0; i < src_count && code == ERR_OK; i++)
            if (!strncmp((src_container + i)->name, substr, strlen(substr)))
            {
                code = copy_thing(dst_container + *dst_count, src_container + i);

                if (code == ERR_OK)
                    (*dst_count)++;
            }
        
    return code;
}

int sort_container(thing_t *container, size_t things_count)
{
    int code = ERR_OK;

    if (!container)
        code = ERR_NULL;
    else
        for (size_t i = 0; i < things_count - 1; i++)
            for (size_t j = i + 1; j < things_count; j++)
                if ((container + i)->weight / (container + i)->volume > (container + j)->weight / (container + j)->volume)
                    swap(container + i, container + j);

    return code;
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

    if (!container)
        code = ERR_NULL;
    else
    {
        thing_t *prefix_container = calloc(count_things, sizeof(thing_t));

        if (prefix_container)
        {
            size_t prefix_count = 0;
            code = copy_names_startswith(container, prefix_container, count_things, &prefix_count, prefix);

            if (prefix_count)
                print_all(prefix_container, prefix_count);
            else
                code = ERR_NO_DATA;

            free_container(prefix_container, prefix_count);
        }
        else
            code = ERR_ALLOC_PREFIX;
    }

    return code;
}

int copy_thing(thing_t *dst, thing_t *src)
{
    int code = ERR_OK;

    if (!dst || !src)
        code = ERR_NULL;
    else
    {
        dst->name = strdup(src->name);
        dst->volume = src->volume;
        dst->weight = src->weight;
    }

    return code;
}
