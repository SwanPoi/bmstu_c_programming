#ifndef LAB_07_IO_FILE_H
#define LAB_07_IO_FILE_H

#include <stdio.h>

int count_digits(FILE *src, int *code);
void read_digits_from_file(FILE *src, int *p_start, int *p_end, int *code);
void write_arr_to_file(FILE *file, int *p_start, int *p_end);

#endif //LAB_07_IO_FILE_H
