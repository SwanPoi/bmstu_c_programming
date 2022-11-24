#ifndef __STRUCT_H__
#define __STRUCT_H__ 

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

typedef struct summand
{
    int multiplier;
    int degree;
} summand_t;

#endif //__STRUCT_H__  
