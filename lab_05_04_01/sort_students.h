#ifndef SORT_H
#define SORT_H

int put_student_by_pos(FILE *file, int position, student_t *student);
student_t get_student_by_pos(FILE *file, int position, int *code);
int compare_students(student_t *left_student, student_t *right_student);
int swap(FILE *file, student_t *left_student, student_t *right_student);
int sort_students(FILE *file);

#endif // SORT_H 
