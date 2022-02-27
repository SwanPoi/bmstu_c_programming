#include <stdio.h>
#include <limits.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_NEGATIVE 2
#define ERR_OVERFLOW 3

void dec_to_bin(unsigned int number);

unsigned int encode(unsigned int number);

int main(void) 
{
    int rc = ERR_OK;
    long int number;
    unsigned long long int encoded_number;

    if (scanf("%li", &number) != 1) 
    {
        rc = ERR_IO;
        printf("Error: input error.\n");
    } 
    else if (number < 0) 
    {
        rc = ERR_NEGATIVE;
        printf("Error: you input negative number.\n");
    } 
    else if (number > UINT_MAX) 
    {
        rc = ERR_OVERFLOW;
        printf("Error: you exceeded size of unsigned int.\n");
    } 
    else 
    {
        encoded_number = encode((unsigned int) number);
        dec_to_bin(encoded_number);
    }

    return rc;
}

void dec_to_bin(unsigned int number) 
{
    printf("Result: ");
    for (int i = 31; i >= 0; i--)
    {
        int bit = (number >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}

unsigned int encode(unsigned int number) 
{
    unsigned int encoded_number = number;
    for (int i = 31; i > 0; i -= 2)
    {
        int left = ((encoded_number >> i) & 1);
        int right = ((encoded_number >> (i - 1)) & 1);
        encoded_number = (((~(1 << i)) & encoded_number) | (right << i));
        encoded_number = (((~(1 << (i - 1))) & encoded_number) | (left << (i-1)));
    }

    return encoded_number;
}
 
