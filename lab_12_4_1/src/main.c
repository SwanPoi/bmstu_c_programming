#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include "../inc/constants.h"
#include "../inc/IO_file.h"
#include "../inc/task_processes.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;

    void *lib = NULL;
    fn_count_digits_ptr count_digits_ptr = NULL;

    #ifndef DYN_LOAD
    count_digits_ptr = count_digits;
    #else
    lib = dlopen("libarr.so", RTLD_NOW);

    if (!lib)
        rc = ERR_OPEN_LIB;
    else
    {
        count_digits_ptr = (fn_count_digits_ptr) dlsym(lib, "count_digits");

        if (!count_digits_ptr)
            rc = ERR_LOAD_FUNCTION;
    }
    #endif

    if (argc == 4 && strcmp(argv[3], "f"))
        rc = ERR_FOURTH_FLAG;
    else if (rc == ERR_OK && (argc == 3 || argc == 4))
    {
        FILE *src = fopen(argv[1], "r");

        if (src)
        {
            int count = count_digits_ptr(src, &rc);
            rewind(src);

            if (rc == ERR_OK && count)
                rc = work_with_arrays(src, count, argc, argv[2], lib);
            else if (!count)
                rc = ERR_EMPTY_SRC_ARRAY;

            fclose(src);
        }
        else
            rc = ERR_OPEN_SRC;
    }
    else
        rc = ERR_COUNT_ARGS;

    #ifdef DYN_LOAD
    if (rc != ERR_OPEN_LIB)
        dlclose(lib);
    #endif

    return rc;
}
