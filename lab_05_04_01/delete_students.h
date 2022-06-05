#ifndef DELETE_H
#define DELETE_H

double get_average_mark(student_t *student);
double get_average_in_file(FILE *file, int count_students, int *code);
int delete_students_by_low_average(FILE *file, char *file_name);
int delete_student(FILE *file, int position, int *count_students);

#endif // DELETE_H
