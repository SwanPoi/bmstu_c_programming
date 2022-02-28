#include <stdio.h>
#include <limits.h>

#define ERR_OK 0
#define ERR_IO 1
#define ODD_BITS 2863311530

void dec_to_bin(unsigned int number);

unsigned int encode(unsigned int number);

int main(void) 
{
    int rc = ERR_OK;
    unsigned int number;
    unsigned int encoded_number;

    if (scanf("%ui", &number) != 1) 
    {
        rc = ERR_IO;
        printf("Error: input error.\n");
    } 
    else 
    {
        encoded_number = encode(number);
        dec_to_bin(encoded_number);
    }

    return rc;
}

void dec_to_bin(unsigned int number) 
{
    printf("Result: ");
    for (int i = 31; i >= 0; i--)
    {
        int bit = (number >> i) % 2;
        printf("%d", bit);
    }
    printf("\n");
}

unsigned int encode(unsigned int number) 
{
    unsigned long encoded_number;

    encoded_number = ((ODD_BITS & number) >> 1) | (((~ODD_BITS & number) << 1));

    return encoded_number;
}
 
