#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "constants.h"
#include "struct.h"
#include "operations.h"
#include "search_startwith.h" 

int is_startwith(char *string, char *substr)
{
    return strstr(string, substr) == string ? TRUE : FALSE;
}

int search_startwith(FILE *src, FILE *dst, char *substr)
{
    int size_of_file = 0;
    int code = check_correct_size_of_file(src, &size_of_file);
    
    if (code == ERR_OK)
    {
        int count_students = size_of_file / STUD_SIZE;
        int count_startwith = 0;
        student_t cur_student;
        
        for (int i = 0; i < count_students && code == ERR_OK; i++)
            if (fread(&cur_student, STUD_SIZE, 1, src) != 1)
                code = ERR_READ;
            else if (is_startwith(cur_student.surname, substr) == TRUE)
            {
                if (fwrite(&cur_student, STUD_SIZE, 1, dst) != 1)
                    code = ERR_WRITE;
                else
                    count_startwith++;
            }
        
        code = count_startwith ? code : ERR_NO_DATA;
    }
    
    return code;
}
