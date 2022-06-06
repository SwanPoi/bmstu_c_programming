#include <stdio.h>
#include "process.h" 

int main(void)
{
    size_t index = 0;
    
    int code = process(stdin, &index);
    
    if (code == ERR_OK)
        printf("%zu\n", index);
    else
        printf("There is no input\n");
    
    return code;
}
