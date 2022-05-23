#include <stdio.h>
#include "process.h" 

int main(void)
{
    size_t index = 0;
    
    int code = process(stdin, &index);
    
    if (code == ERR_OK)
        fprintf(stdout, "%zu\n", index);
    else
        fprintf(stderr, "There is no input\n");
    
    return code;
}
