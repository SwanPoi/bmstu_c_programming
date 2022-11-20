#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include "../inc/constants.h"
#include "../inc/polynomial_process.h"

int main(void)
{
    int rc = ERR_OK;

    size_t len_mode = 0;
    char *mode = NULL;

    if (getline(&(mode), &len_mode, stdin) != -1)
    {
        if (strcmp(mode, "val\n") == 0)
        {
            rc = val_process();
        }
        else if (strcmp(mode, "ddx\n") == 0)
        {
            rc = ddx_process();
        }
        else if (strcmp(mode, "sum\n") == 0)
        {
            rc = sum_process();
        }
        else if (strcmp(mode, "dvd\n") == 0)
        {
            rc = dvd_process();
        }
        else
            rc = ERR_MODE;
    }
    else
        rc = ERR_INVALID_ARGS;
    
    return rc;
}
