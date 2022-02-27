#include <stdio.h>
#include <limits.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_NEGATIVE 2
#define ERR_OVERFLOW 3
#define ERR_TOO_BIG 4

void dec_to_bin(unsigned int number);

unsigned int get_even_bits(unsigned int number);

unsigned int get_odd_bits(unsigned int number);

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

unsigned int get_even_bits(unsigned int number) 
{
    return ((number & 2863311530)) >> 1;
}

unsigned int get_odd_bits(unsigned int number) 
{
    return (number & 1431655765) << 1;
}

unsigned int encode(unsigned int number) 
{
    unsigned int odd_bits = get_odd_bits(number), even_bits = get_even_bits(number);
    unsigned int encoded_number = odd_bits + even_bits;

    return encoded_number;
}
 
