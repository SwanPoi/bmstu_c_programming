#ifndef __STRUCT_H__
#define __STRUCT_H__ 

#define STRING_LENGTH 25

typedef struct thing
{
    char name[STRING_LENGTH + 2];
    double weight;
    double volume;
} thing_t;

#define THING_SIZE sizeof(thing_t)

#endif //__STRUCT_H__  
