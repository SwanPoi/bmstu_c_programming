#ifndef STRUCT_H
#define STRUCT_H 

#define NAME 10
#define SURNAME 25
#define MARKS 4

typedef struct student
{
    char surname[SURNAME + 1];
    char name[NAME + 1];
    uint32_t marks[MARKS];
} student_t;

#define STUD_SIZE sizeof(student_t)

#endif //STRUCT_H 
