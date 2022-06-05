#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include "struct.h"
#include "operations.h"

int check_correct_size_of_file(FILE *file, int *size)
{
    int code = ERR_OK;
    
    if (fseek(file, 0, SEEK_END) || ftell(file) == -1L)
        code = ERR_READ;
    else if (ftell(file) % STUD_SIZE != 0)
        code = ERR_INVALID_SIZE;
    else
        *size = ftell(file);
    
    rewind(file);
    
    return code;    
} 

int print_from_file(FILE *file)
{
    int size = 0;
    int code = check_correct_size_of_file(file, &size);
    
    if (code == ERR_OK)
    {
        student_t cur_student;
        
        if (fread(&cur_student, STUD_SIZE, 1, file) == 1)
        {
            print_structure(&cur_student);
            
            while (fread(&cur_student, STUD_SIZE, 1, file) == 1)
                print_structure(&cur_student);
        }
        else
            code = ERR_READ;
    }
    
    return code;
}

void print_structure(student_t *student)
{
    printf("%s\n%s\n", student->surname, student->name);
    
    for (int i = 0; i < MARKS; i++)
        printf("%u ", student->marks[i]);
    
    printf("\n");
}
