#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "struct.h"
#include "constants.h"
#include "operations.h"
#include "delete_students.h"

double get_average_mark(student_t *student)
{
    double sum = 0;
    
    for (int i = 0; i < MARKS; i++)
        sum += student->marks[i];
    
    return sum / MARKS;
}

double get_average_in_file(FILE *file, int count_students, int *code)
{
    double sum_of_averages = 0;
    student_t cur_student;
        
    for (int i = 0; i < count_students && *code == ERR_OK; i++)
        if (fread(&cur_student, STUD_SIZE, 1, file) != 1)
            *code = ERR_READ;
        else
            sum_of_averages += get_average_mark(&cur_student);
    
    rewind(file);
    
    return sum_of_averages / count_students;    
}

int delete_student(FILE *file, int position, int *count_students)
{
    int code = ERR_OK;
    student_t student;
    
    for (int i = position; i < (*count_students) - 1 && code == ERR_OK; i++)
        if (fread(&student, STUD_SIZE, 1, file) != 1)
            code = ERR_READ;
        else if (fseek(file, i * STUD_SIZE, SEEK_SET) != 0)
            code = ERR_FSEEK;
        else if (fwrite(&student, STUD_SIZE, 1, file) != 1)
            code = ERR_WRITE;
        else if (fseek(file, STUD_SIZE, SEEK_CUR) != 0)
            code = ERR_FSEEK;
      
    if (code == ERR_OK)
    {
        (*count_students)--;
        
        if (fseek(file, position * STUD_SIZE, SEEK_SET) != 0)
            code = ERR_FSEEK;
    }
    
    return code;
}

int delete_students_by_low_average(FILE *file, char *file_name)
{
    int size_of_file = 0;
    int code = check_correct_size_of_file(file, &size_of_file);
    
    if (code == ERR_OK)
    {
        int count_students = size_of_file / STUD_SIZE;
        double average_in_file = get_average_in_file(file, count_students, &code);
        
        if (code == ERR_OK)
        {
            student_t cur_student;
            
            for (int i = 0; i < count_students && code == ERR_OK; i++)
                if (fread(&cur_student, STUD_SIZE, 1, file) != 1)
                    code = ERR_READ;
                else if (get_average_mark(&cur_student) < average_in_file)
                {
                    code = delete_student(file, i, &count_students);
                    i--;
                }

            truncate(file_name, count_students * STUD_SIZE);
        }
    }
    
    return code;
}
