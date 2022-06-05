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
    long int start_pos = ftell(file);
    
    if (fseek(file, position, SEEK_SET))
        code = ERR_INVALID_POS;
    else if (fwrite(student, STUD_SIZE, 1, file) != 1)
        code = ERR_WRITE;
    else
        fseek(file, start_pos, SEEK_SET);
    
    return code;
}

student_t get_student_by_pos(FILE *file, int position, int *code)
{
    student_t student;
    long int start_pos = ftell(file);
    
    if (fseek(file, position, SEEK_SET) || fread(&student, STUD_SIZE, 1, file) != 1)
        *code = ERR_INVALID_POS;
    else
        fseek(file, start_pos, SEEK_SET);
    
    return student;
}

int compare_students(student_t *left_student, student_t *right_student)
{
    int compare_surnames = strcmp(left_student->surname, right_student->surname);
    
    return compare_surnames != 0 ? compare_surnames : strcmp(left_student->name, right_student->name);
}

int swap(FILE *file, int left_pos, int right_pos)
{
    int code = ERR_OK;
    
    student_t stud_left = get_student_by_pos(file, left_pos, &code);
    if (code == ERR_OK)
    {
        student_t stud_right = get_student_by_pos(file, right_pos, &code);
        
        if (code == ERR_OK)
        {
            code = put_student_by_pos(file, left_pos, &stud_right);
            
            if (code == ERR_OK)
                code = put_student_by_pos(file, right_pos, &stud_left);
        }
    }
    
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
        
        int is_sorted = FALSE;
        
        for (int i = 0; i < count_students - 1 && is_sorted == FALSE && code == ERR_OK; i++)
        {
            is_sorted = TRUE;
            
            for (int j = 0; j < count_students - i - 1 && code == ERR_OK; j++)
            {
                student_t student_left = get_student_by_pos(file, j * STUD_SIZE, &code);
                student_t student_right = get_student_by_pos(file, (j + 1) * STUD_SIZE, &code);
                
                if (code == ERR_OK && compare_students(&student_left, &student_right) > 0)
                {
                    code = swap(file, j * STUD_SIZE, (j + 1) * STUD_SIZE);
                    is_sorted = FALSE;
                }
            }
        }
    }
    
    return code;
}
