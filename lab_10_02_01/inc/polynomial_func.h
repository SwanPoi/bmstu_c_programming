#ifndef __POLYNOMIAL_FUNC_H__
#define __POLYNOMIAL_FUNC_H__

#include "struct.h"

int count_polynomial(node_t *polynomial, int x);
void derivative(node_t *polynomial);
node_t *sum_polynomials(node_t *first, node_t *second, int *rc);
int split_odds_and_evens(node_t *src, node_t **evens, node_t **odds);

#endif // __POLYNOMIAL_FUNC_H__
