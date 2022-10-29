#ifndef __PROCESS_H__
#define __PROCESS_H__ 

#include "struct.h"

size_t copy_names_startswith(thing_t *src_container, thing_t *dst_container, size_t src_count, char *substr);
void sort_container(thing_t *container, size_t things_count);
void swap(thing_t *first, thing_t *second);
int prefix_process(thing_t *container, size_t count_things, char *prefix);

#endif //__PROCESS_H__
