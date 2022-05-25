#ifndef OPERATIONS_H
#define OPERATIONS_H 

int read_structure(FILE *file, student *student);
void print_structure(student *student);
int count_of_structures_in_file(FILE *file, int *code);
int fill_group(FILE *file, student *group, int count);
void print_group(student *group, int count);
int put_struct_in_file(FILE *dst, student *student);
int put_all_structs_in_file(FILE *dst, student *group, int count);
int init_array_of_structs(FILE *file, int *count_structures, student *group);

#endif //OPERATIONS_H
