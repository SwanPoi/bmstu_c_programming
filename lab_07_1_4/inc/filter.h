#ifndef LAB_07_FILTER_H
#define LAB_07_FILTER_H

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
int count_more_than_mean_elements(const int *p_begin, const int *p_end, double mean);
double arithmetic_mean(const int *p_begin, const int *p_end);
void copy_more_than_mean_elements(const int *pb_src, const int *pe_src, int *pb_dst, double mean);

#endif //LAB_07_FILTER_H
