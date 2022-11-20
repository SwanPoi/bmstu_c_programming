#ifndef __STRUCT_H__
#define __STRUCT_H__ 

#define STRING_LENGTH 25

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

typedef struct film
{
    char *name;
    int ticket_price;
} film_t;

#endif //__STRUCT_H__  
