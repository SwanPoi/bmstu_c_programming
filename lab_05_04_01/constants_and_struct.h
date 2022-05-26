#ifndef CONST_H
#define CONST_H

#define ERR_OK 0
#define ERR_INVALID_ARGS 53
#define ERR_WRITE 3
#define ERR_OPEN 4
#define ERR_READ_STRING 5
#define ERR_READ 6
#define ERR_READ_MARKS 7
#define ERR_WRITE_NAME 8

#define NAME 10
#define SURNAME 25
#define MARKS 4

#define NMAX 100
#define HERE 1
#define NOT_HERE 0

typedef struct student
{
    char surname[SURNAME];
    char name[NAME];
    uint32_t marks[MARKS];
} student;


#endif //CONST_H 
