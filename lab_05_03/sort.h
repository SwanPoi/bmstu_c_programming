#ifndef SORT_H
#define SORT_H 

int_type get_number_by_pos(FILE *file, int positions, int *code);
int put_number_by_pos(FILE *file, int position, int_type number);
int swap(FILE *file, int left_pos, int right_pos);
int sort(FILE *file);

#endif //SORT_H
