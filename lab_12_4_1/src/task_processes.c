#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "../inc/sort.h"
#include "../inc/filter.h"
#include "../inc/IO_file.h"
#include "../inc/constants.h"
#include "../inc/task_processes.h"

int new_array_process(int *src_array_start, int *src_array_end, char *filename, int count_args, void *lib)
{
    int rc = ERR_OK;

    int *dst_array_start = NULL;
    int *dst_array_end = NULL;
    fn_key_ptr key_ptr = NULL;
    fn_comp_ptr comp_int_ptr = NULL;
    fn_mysort_ptr mysort_ptr = NULL;
    fn_write_ptr write_with_validate_ptr = NULL;

    #ifndef DYN_LOAD
        if (lib != NULL)
            rc = ERR_NULL_POINTER;

        key_ptr = key;
        comp_int_ptr = comp_int;
        mysort_ptr = mysort;
        write_with_validate_ptr = write_with_validate;
    #else
        key_ptr = (fn_key_ptr) dlsym(lib, "key");
        comp_int_ptr = (fn_comp_ptr) dlsym(lib, "comp_int");
        mysort_ptr = (fn_mysort_ptr) dlsym(lib, "mysort");
        write_with_validate_ptr = (fn_write_ptr) dlsym(lib, "write_with_validate");

        if (!key_ptr || !comp_int_ptr || !mysort_ptr || !write_with_validate_ptr)
            rc = ERR_LOAD_FUNCTION;
    #endif

    if (count_args == 4 && rc == ERR_OK)
    {
        int count_numbers_in_dst = 0;
        rc = key_ptr((const int *) src_array_start, (const int *) src_array_end, dst_array_start, &count_numbers_in_dst);
        
        dst_array_start = calloc(count_numbers_in_dst, sizeof(int));

        if (dst_array_start)
        {
            dst_array_end = dst_array_start + count_numbers_in_dst;
            rc = key_ptr((const int *) src_array_start, (const int *) src_array_end, dst_array_start, &count_numbers_in_dst);
        }
            
        else
            rc = ERR_PB_DST;
    }
    else if (rc == ERR_OK)
    {
        dst_array_start = src_array_start;
        dst_array_end = src_array_end;
    }

    if (rc == ERR_OK)
    {
        mysort_ptr(dst_array_start, dst_array_end - dst_array_start, sizeof(int), comp_int_ptr);

        rc = write_with_validate_ptr(filename, dst_array_start, dst_array_end);
    }

    if (count_args == 4 && rc != ERR_LOAD_FUNCTION)
    {
        free(dst_array_start);
        dst_array_start = NULL;
    }

    return rc;
}

int work_with_arrays(FILE *src, int count_digits, int count_args, char *dst_name, void *lib)
{
    int rc = ERR_OK;

    fn_read_ptr read_digits_from_file_ptr = NULL;

    #ifndef DYN_LOAD
        if (lib != NULL)
            rc = ERR_NULL_POINTER;
            
        read_digits_from_file_ptr = read_digits_from_file;
    #else
    
        read_digits_from_file_ptr = (fn_read_ptr) dlsym(lib, "read_digits_from_file");

        if (!read_digits_from_file_ptr)
        {
            rc = ERR_LOAD_FUNCTION;
        }
    #endif

    int *src_array_start = calloc(count_digits, sizeof(int));

    if (src_array_start)
    {
        int *src_array_end = NULL;

        if (rc == ERR_OK)
        {
            src_array_end = src_array_start + count_digits;
            read_digits_from_file_ptr(src, src_array_start, src_array_end, &rc);
        }

        if (rc == ERR_OK)
            rc = new_array_process(src_array_start, src_array_end, dst_name, count_args, lib);
    }
    else
        rc = ERR_SRC_MEMORY;

    free(src_array_start);
    src_array_start = NULL;

    return rc;
}