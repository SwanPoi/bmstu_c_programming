#ifndef __LIST_FUNCTIONS__
#define __LIST_FUNCTIONS__

#include "struct.h"

void *pop_front(node_t **head);
void *pop_back(node_t **head);
void append(node_t **head_a, node_t **head_b);
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));
void front_back_split(node_t *head, node_t **back);
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));
int films_comparator(const void *first, const void *second);

#endif // __LIST_FUNCTIONS__