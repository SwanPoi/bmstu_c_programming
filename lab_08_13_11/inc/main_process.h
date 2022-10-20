#ifndef LAB_08_MAIN_PROCESS_H
#define LAB_08_MAIN_PROCESS_H

#include <stdio.h>

int det_print(char *dst_name, double det);
double det_search(double **matrix, int rows, int columns, int *rc);
int det_process(char *src_name, char *dst_name);
int process_with_open_files(FILE *first_file, FILE *second_file, FILE *res_file, char *mode);
int add_mult_process(char *first_name, char *second_name, char *res_name, char *mode);

#endif //LAB_08_MAIN_PROCESS_H
