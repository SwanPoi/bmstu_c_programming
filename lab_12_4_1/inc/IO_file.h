#ifndef LAB_07_IO_FILE_H
#define LAB_07_IO_FILE_H

#include <stdio.h>

int count_digits(FILE *src, int *code);
void read_digits_from_file(FILE *src, int *p_start, int *p_end, int *code);
int write_with_validate(char *filename, int *p_start, int *p_end);

#endif //LAB_07_IO_FILE_H
