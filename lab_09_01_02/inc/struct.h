#ifndef __STRUCT_H__
#define __STRUCT_H__ 

#define STRING_LENGTH 25

typedef struct thing
{
    char *name;
    double weight;
    double volume;
} thing_t;

#define THING_SIZE sizeof(thing_t)

#endif //__STRUCT_H__  
