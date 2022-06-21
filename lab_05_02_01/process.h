#ifndef PROCESS_H
#define PROCESS_H

int more_than_avrg_of_max_and_min(FILE *file, int *code);
void get_max_and_min(FILE *file, double *max, double *min, int *code);
int count_more_than(FILE *file, double to_compare);

#endif //PROCESS_H 
