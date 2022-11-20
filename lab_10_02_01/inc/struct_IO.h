#ifndef __STRUCT_IO__
#define __STRUCT_IO__

#include <stdio.h>
#include "struct.h"

int read_structure(FILE *file, summand_t *sum);
int print_structure(FILE *file, summand_t *sum);
int print_all(FILE *file, node_t *polynomial);
void free_list(node_t *polynomial);
int init_struct_list(FILE *file, node_t **polynomial);

#endif // __STRUCT_IO__
