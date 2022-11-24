#ifndef __STRUCT_IO__
#define __STRUCT_IO__

#include <stdio.h>
#include "struct.h"

int read_structure(FILE *file, film_t *film);
int print_structure(FILE *file, film_t *film);
int print_all(FILE *file, node_t *films);
void free_list(node_t *films);
void free_film(film_t *film);
int init_struct_list(FILE *file, node_t **films);

#endif // __STRUCT_IO__