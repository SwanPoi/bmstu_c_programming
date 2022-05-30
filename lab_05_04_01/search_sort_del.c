#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "constants_and_struct.h"
#include "read_write_structure.h"
#include "search_sort_del.h"

// Пункт b): поиск и вывод студентов, фамилии которых начинаются с подстроки
int search_and_write(FILE *src, FILE *dst, char *substr)
{
    int count_structures;
    student group[NMAX];
    
    int code = init_array_of_structs(src, &count_structures, group);
    
    if (code == ERR_OK)
    {
        student group_startwith[NMAX];
            
        int count_startswith = form_arr_startwith(group, count_structures, group_startwith, substr);

        code = put_all_structs_in_file(dst, group_startwith, count_startswith);
        
        if (code == ERR_OK)
            print_group(group_startwith, count_startswith);
    }
    
    return code;
}

// Формирование массива структур студентов, фамилии которых начинаются с подстроки
int form_arr_startwith(student *group, int count_group, student *startswith, char *substr)
{
    int count_startswith = 0;
    
    for (int i = 0; i < count_group; i++)
        if (strstr(group[i].surname, substr) == group[i].surname)
        {
            startswith[count_startswith] = group[i];
            count_startswith++;
        }
        
    return count_startswith;
}

// Пункт a): сортировка структур по фамилиям и, если они совпадают, по именам
int sort_in_file(char *filename)
{
    int code = ERR_OK;
    int count_structures;
    student group[NMAX];
    FILE *file = fopen(filename, "r");
    
    if (file)
    {
        code = init_array_of_structs(file, &count_structures, group);
        
        if (code == ERR_OK)
            sort_structures(group, count_structures);
            
        fclose(file);
        
        if (code == ERR_OK)
        {
            file = fopen(filename, "w");
                
            if (file)
            {
                code = put_all_structs_in_file(file, group, count_structures);
                    
                if (code == ERR_OK)
                    print_group(group, count_structures);
            }
            else
                code = ERR_OPEN;
            
            fclose(file);
        }
    }
    else
        code = ERR_OPEN;
    
    return code;
}

// Сортировка студентов по фамилиям
void sort_structures(student *group, int count)
{
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (compare_students(group + i, group + j) > 0)
                swap_structures(group + i, group + j);
}

// Сравнение двух студентов по фамилиям и, если они одинаковые, по именам
int compare_students(student *left_student, student *right_student)
{
    int compare_surnames = strcmp(left_student->surname, right_student->surname);
    
    return compare_surnames != 0 ? compare_surnames : strcmp(left_student->name, right_student->name);
}

// Перестановка местами двух структур в массиве
void swap_structures(student *left, student *right)
{
    student temporary = *left;
    *left = *right;
    *right = temporary;
}

// Удаление студентов, у которых средняя оценка меньше 
int delete_from_file(char *filename)
{
    int code = ERR_OK;
    int count_structures = 0;
    student group[NMAX];
    
    FILE *file = fopen(filename, "r");
    
    if (file)
    {
        code = init_array_of_structs(file, &count_structures, group);
        
        if (code == ERR_OK)
        {
            double average_in_file = get_average_mark_in_whole(group, count_structures);
            
            do_removal(group, &count_structures, average_in_file);
        }
        
        fclose(file);
        
        if (code == ERR_OK)
        {
            file = fopen(filename, "w");
            
            if (file)
            {
                code = put_all_structs_in_file(file, group, count_structures);
                
                if (code == ERR_OK)
                    print_group(group, count_structures);
            }
            else
                code = ERR_OPEN;
                
            fclose(file);
        }
    }
    else
        code = ERR_OPEN;
    
    return code;
}

// Получение суммы оценок студента
double sum_student_marks(student *student)
{
    double sum = 0;
    
    for (int i = 0; i < MARKS; i++)
        sum += student->marks[i];
    
    return sum;
}

// Получение средней оценки по всем студентам
double get_average_mark_in_whole(student *group, int count)
{
    double sum = 0;
    
    for (int i = 0; i < count; i++)
        sum += sum_student_marks(group + i);
    
    return sum / (MARKS * count);
}

// Удаление студента из массива
void delete_student(student *group, int *count, int index)
{
    for (int i = index; i < *count - 1; i++)
        group[i] = group[i + 1];
    
    (*count)--;
}

// Удаление студентов, чьи средние оценки меньше средней общей оценки
void do_removal(student *group, int *count, double average_in_file)
{
    int index = 0;
    
    while (index < *count)
    {
        double average = sum_student_marks(group + index) / MARKS;
        
        if (average < average_in_file)
            delete_student(group, count, index);
        else
            index++;
    }
}
