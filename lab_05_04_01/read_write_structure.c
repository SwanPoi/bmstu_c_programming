#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "constants_and_struct.h"
#include "read_write_structure.h"

// Считывание структуры из файла
int read_structure(FILE *file, student *student)
{
    int code = ERR_OK;
    
    if (!feof(file) && fscanf(file, "%s", student->surname) == 1 && strlen(student->surname) <= SURNAME)
    {
        if (!feof(file) && fscanf(file, "%s", student->name) == 1 && strlen(student->name) <= NAME)
        {
            for (int i = 0; i < MARKS && code == ERR_OK; i++)
                if (fscanf(file, "%u", (student->marks + i)) != 1)
                    code = ERR_READ_MARKS;
        }
        else
            code = ERR_READ;
        
         fscanf(file, "\n");
    }
    else
        code = ERR_READ_STRING;
    
    return code;
}

// Вывод структуры на экран
void print_structure(student *student)
{
    printf("%s\n%s\n", student->surname, student->name);
    
    for (int i = 0; i < MARKS; i++)
        printf("%u ", student->marks[i]);
    
    printf("\n");
}

// Подсчет количества структур в файле
int count_of_structures_in_file(FILE *file, int *code)
{
    int count = 0;
    student student;
    
    while (!feof(file) && *code == ERR_OK)
    {
        *code = read_structure(file, &student);
        
        if (*code == ERR_OK)
            count++;
    }
    
    return count;
}

// Заполнение массива структур из файла
int fill_group(FILE *file, student *group, int count)
{
    int code = ERR_OK;
    
    for (int i = 0; i < count && code == ERR_OK; i++)
        code = read_structure(file, group + i);
    
    return code;
}

// Печать массива структур
void print_group(student *group, int count)
{
    for (int i = 0; i < count; i++)
        print_structure(group + i);
}

// Запись структуры в файл
int put_struct_in_file(FILE *dst, student *student)
{
    int code = ERR_OK;
    
    if (fprintf(dst, "%s\n", student->surname) > -1 && fprintf(dst, "%s\n", student->name) > -1)
    {
        for (int i = 0; i < MARKS && code == ERR_OK; i++)
            if (fprintf(dst, "%u ", student->marks[i]) < 0)
                code = ERR_WRITE;
            
        if (fprintf(dst, "\n") != 1)
            code = ERR_WRITE;
    }
    else
        code = ERR_WRITE_NAME;

    return code;
}

// Запись массива структур в файл
int put_all_structs_in_file(FILE *dst, student *group, int count)
{
    int code = ERR_OK;
    
    for (int i = 0; i < count && code == ERR_OK; i++)
        code = put_struct_in_file(dst, group + i);
    
    return code;
}

// Формирование массива структур из файла
int init_array_of_structs(FILE *file, int *count_structures, student *group)
{
    int code = ERR_OK;
    
    *count_structures = count_of_structures_in_file(file, &code);
    rewind(file);
    
    if (code == ERR_OK)
        code = fill_group(file, group, *count_structures);
    
    return code;
}
