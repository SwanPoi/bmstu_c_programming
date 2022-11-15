#ifndef LAB_08_STRUCT_H
#define LAB_08_STRUCT_H

typedef struct matrix
{
    double **data;
    int rows;
    int columns;
} matrix_t;

typedef struct array
{
    int *data;
    int size;
} array_t;

#endif //LAB_08_STRUCT_H
