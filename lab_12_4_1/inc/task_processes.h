#ifndef NEW_LAB_07_TASK_PROCESSES_H
#define NEW_LAB_07_TASK_PROCESSES_H

typedef int (*fn_comp_ptr)(const void*, const void *);
typedef void (*fn_mysort_ptr)(void *, size_t, size_t, fn_comp_ptr);
typedef int (*fn_key_ptr)(const int *, const int *, int *, int *);
typedef int (*fn_count_digits_ptr)(FILE *, int *);
typedef void (*fn_read_ptr)(FILE *, int *, int *, int *);
typedef int (*fn_write_ptr)(char *, int *, int *);

int new_array_process(int *src_array_start, int *src_array_end, char *filename, int count_args, void*lib);
int work_with_arrays(FILE *src, int count_digits, int count_args, char *dst_name, void *lib);

#endif //NEW_LAB_07_TASK_PROCESSES_H
