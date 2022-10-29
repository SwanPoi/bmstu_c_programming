#ifndef __STRUCTIO_H__
#define __STRUCTIO_H__

#include <stdio.h>
#include "struct.h"

int read_structure(FILE *file, thing_t *thing);
int check_correct_string(char *string, int size);
void print_structure(thing_t *thing);
void print_all(thing_t *container, size_t count_things);
int init_struct_array(FILE *file, thing_t **container, size_t *count_things);
int count_of_structures_in_file(FILE *file, int *code);

void free_container(thing_t *container, size_t count_things);
int realloc_container(thing_t **container, size_t cur_count, size_t *alloc_count);

#endif //__STRUCTIO_H__
