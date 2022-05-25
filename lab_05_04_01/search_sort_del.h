#ifndef SEARCH_H
#define SEARCH_H

int search_and_write(FILE *src, FILE *dst, char *substr);
int form_arr_startwith(Student *group, int count_group, Student *startswith, char *substr);
int sort_in_file(FILE *file);
void sort_structures(Student *group, int count);
int compare_students(Student *left, Student *right_student);
void swap_structures(Student *left, Student *right);
int delete_from_file(char *filename);
double sum_student_marks(Student *student);
double get_average_mark_in_whole(Student *group, int count);
void delete_student(Student *group, int *count, int index);
void do_removal(Student *group, int *count, double average_in_file);

#endif // SEARCH_H
