#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "struct.h"
#include "constants.h"
#include "operations.h"
#include "sort_students.h" 

int put_student_by_pos(FILE *file, int position, student_t *student)
{
    int code = ERR_OK;
    
    if (fseek(file, position, SEEK_SET))
        code = ERR_INVALID_POS;
    else if (fwrite(student, STUD_SIZE, 1, file) != 1)
        code = ERR_WRITE;
    
    return code;
}

student_t get_student_by_pos(FILE *file, int position, int *code)
{
    student_t student;
    
    if (fseek(file, position, SEEK_SET) || fread(&student, STUD_SIZE, 1, file) != 1)
        *code = ERR_INVALID_POS;
    
    return student;
}

int compare_students(student_t *left_student, student_t *right_student)
{
    int compare_surnames = strcmp(left_student->surname, right_student->surname);
    
    return compare_surnames != 0 ? compare_surnames : strcmp(left_student->name, right_student->name);
}

int swap(FILE *file, student_t *left_student, student_t *right_student)
{
    int code = ERR_OK;
    int position = ftell(file);
    
    code = put_student_by_pos(file, position - 2 * STUD_SIZE, right_student);
            
    if (code == ERR_OK)
        code = put_student_by_pos(file, position - STUD_SIZE, left_student);
    
    return code;
}

int sort_students(FILE *file)
{
    int code = ERR_OK;
    int size_of_file = 0;
    
    code = check_correct_size_of_file(file, &size_of_file);
    
    if (code == ERR_OK)
    {
        int count_students = size_of_file / STUD_SIZE;
        
        for (int i = 0; i < count_students - 1 && code == ERR_OK; i++)
            for (int j = 0; j < count_students - i - 1 && code == ERR_OK; j++)
            {
                student_t student_left = get_student_by_pos(file, j * STUD_SIZE, &code);
                student_t student_right = get_student_by_pos(file, (j + 1) * STUD_SIZE, &code);
                
                if (code == ERR_OK && compare_students(&student_left, &student_right) > 0)
                    code = swap(file, &student_left, &student_right);
            }
    }
    
    return code;
}
