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
    Student group[NMAX];
    
    int code = init_array_of_structs(src, &count_structures, group);
    
    if (code == ERR_OK)
    {
        Student group_startwith[NMAX];
            
        int count_startswith = form_arr_startwith(group, count_structures, group_startwith, substr);

        print_group(group_startwith, count_startswith);
        code = put_all_structs_in_file(dst, group_startwith, count_startswith);
    }
    
    return code;
}

// Формирование массива структур студентов, фамилии которых начинаются с подстроки
int form_arr_startwith(Student *group, int count_group, Student *startswith, char *substr)
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
int sort_in_file(FILE *file)
{
    int count_structures;
    Student group[NMAX];
    
    int code = init_array_of_structs(file, &count_structures, group);
    
    if (code == ERR_OK)
    {
        sort_structures(group, count_structures);
        
        print_group(group, count_structures);
    }
    
    return code;
}

// Сортировка студентов по фамилиям
void sort_structures(Student *group, int count)
{
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (compare_students(group + i, group + j) > 0)
                swap_structures(group + i, group + j);
}

// Сравнение двух студентов по фамилиям и, если они одинаковые, по именам
int compare_students(Student *left_student, Student *right_student)
{
    int compare_surnames = strcmp(left_student->surname, right_student->surname);
    
    return compare_surnames != 0 ? compare_surnames : strcmp(left_student->name, right_student->name);
}

// Перестановка местами двух структур в массиве
void swap_structures(Student *left, Student *right)
{
    Student temporary = *left;
    *left = *right;
    *right = temporary;
}

// Удаление студентов, у которых средняя оценка меньше 
int delete_from_file(char *filename)
{
    int code = ERR_OK;
    int count_structures = 0;
    Student group[NMAX];
    
    FILE *file = fopen(filename, "r");
    
    if (file)
    {
        code = init_array_of_structs(file, &count_structures, group);
        
        if (code == ERR_OK)
        {
            double average_in_file = get_average_mark_in_whole(group, count_structures);
            
            do_removal(group, &count_structures, average_in_file);
            
            print_group(group, count_structures);
        }
        
        fclose(file);
        
        if (code == ERR_OK)
        {
            file = fopen(filename, "w");
            
            if (file)
                code = put_all_structs_in_file(file, group, count_structures);
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
double sum_student_marks(Student *student)
{
    double sum = 0;
    
    for (int i = 0; i < MARKS; i++)
        sum += student->marks[i];
    
    return sum;
}

// Получение средней оценки по всем студентам
double get_average_mark_in_whole(Student *group, int count)
{
    double sum = 0;
    
    for (int i = 0; i < count; i++)
        sum += sum_student_marks(group + i);
    
    return sum / (MARKS * count);
}

// Удаление студента из массива
void delete_student(Student *group, int *count, int index)
{
    for (int i = index; i < *count - 1; i++)
        group[i] = group[i + 1];
    
    (*count)--;
}

// Удаление студентов, чьи средние оценки меньше средней общей оценки
void do_removal(Student *group, int *count, double average_in_file)
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
