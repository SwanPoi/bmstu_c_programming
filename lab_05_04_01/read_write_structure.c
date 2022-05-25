#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "constants_and_struct.h"
#include "read_write_structure.h"

// Считывание структуры из файла
int read_structure(FILE *file, Student *student)
{
    int code = ERR_OK;
    
    if (!feof(file) && fgets(student->surname, SURNAME + 1, file) != NULL && check_correct_string(student->surname, SURNAME) == ERR_OK)
    {
        if (!feof(file) && fgets(student->name, NAME + 1, file) != NULL && check_correct_string(student->name, NAME) == ERR_OK)
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
void print_structure(Student *student)
{
    printf("%s%s", student->surname, student->name);
    
    for (int i = 0; i < MARKS; i++)
        printf("%u ", student->marks[i]);
    
    printf("\n");
}

// Проверка корректности строки
int check_correct_string(char *string, int size)
{
    int code = ERR_OK;
    int len = strlen(string);
    
    if (len > size || len == 0 || *(string + len - 1) != '\n')
        code = ERR_READ_STRING;
    else
        for (; *string != '\n' && code == ERR_OK; string++)
            if (!isalpha(*string))
                code = ERR_READ_STRING;
            
    return code;
}

// Подсчет количества структур в файле
int count_of_structures_in_file(FILE *file, int *code)
{
    int count = 0;
    Student student;
    
    while (!feof(file) && *code == ERR_OK)
    {
        *code = read_structure(file, &student);
        
        if (*code == ERR_OK)
            count++;
    }
    
    return count;
}

// Заполнение массива структур из файла
int fill_group(FILE *file, Student *group, int count)
{
    int code = ERR_OK;
    
    for (int i = 0; i < count && code == ERR_OK; i++)
        code = read_structure(file, group + i);
    
    return code;
}

// Печать массива структур
void print_group(Student *group, int count)
{
    for (int i = 0; i < count; i++)
        print_structure(group + i);
}

// Запись структуры в файл
int put_struct_in_file(FILE *dst, Student *student)
{
    int code = ERR_OK;
    
    if (fprintf(dst, "%s", student->surname) > -1 && fprintf(dst, "%s", student->name) > -1)
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
int put_all_structs_in_file(FILE *dst, Student *group, int count)
{
    int code = ERR_OK;
    
    for (int i = 0; i < count && code == ERR_OK; i++)
        code = put_struct_in_file(dst, group + i);
    
    return code;
}

// Формирование массива структур из файла
int init_array_of_structs(FILE *file, int *count_structures, Student *group)
{
    int code = ERR_OK;
    
    *count_structures = count_of_structures_in_file(file, &code);
    rewind(file);
    
    if (code == ERR_OK)
        code = fill_group(file, group, *count_structures);
    
    return code;
}
