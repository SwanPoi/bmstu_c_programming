#ifndef SEARCH_H
#define SEARCH_H

int search_and_write(FILE *src, FILE *dst, char *substr);
int form_arr_startwith(student *group, int count_group, student *startswith, char *substr);
int sort_in_file(FILE *file);
void sort_structures(student *group, int count);
int compare_students(student *left, student *right_student);
void swap_structures(student *left, student *right);
int delete_from_file(char *filename);
double sum_student_marks(student *student);
double get_average_mark_in_whole(student *group, int count);
void delete_student(student *group, int *count, int index);
void do_removal(student *group, int *count, double average_in_file);

#endif // SEARCH_H
