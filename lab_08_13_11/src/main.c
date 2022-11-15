#include <string.h>
#include "../inc/constants.h"
#include "../inc/main_process.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;

    if (argc == 5 && (!strcmp(argv[1], "a") || !strcmp(argv[1], "m")))
        rc = add_mult_process(argv[2], argv[3], argv[4], argv[1]);
    else if (argc == 4 && !strcmp(argv[1], "o"))
        rc = det_process(argv[2], argv[3]);
    else
        rc = ERR_ARGS;

    return rc;
}
