#ifndef OPERATIONS_H
#define OPERATIONS_H 

int read_structure(FILE *file, Student *student);
void print_structure(Student *student);
int check_correct_string(char *string, int size);
int count_of_structures_in_file(FILE *file, int *code);
int fill_group(FILE *file, Student *group, int count);
void print_group(Student *group, int count);
int put_struct_in_file(FILE *dst, Student *student);
int put_all_structs_in_file(FILE *dst, Student *group, int count);
int init_array_of_structs(FILE *file, int *count_structures, Student *group);

#endif //OPERATIONS_H
