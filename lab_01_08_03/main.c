#include <stdio.h>
#include <limits.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_NEGATIVE 2
#define ERR_OVERFLOW 3
#define ERR_TOO_BIG 4

unsigned long long int dec_to_bin(unsigned int number);

unsigned int get_even_bits(unsigned int number);

unsigned int get_odd_bits(unsigned int number);

unsigned long long int encode(unsigned int number);

int main(void) 
{
    int rc = ERR_OK;
    long int number;
    unsigned long long int encoded_number;

    if (scanf("%li", &number) != 1) 
    {
        rc = ERR_IO;
        printf("Error: input error.\n");
    } else if (number < 0) 
    {
        rc = ERR_NEGATIVE;
        printf("Error: you input negative number.\n");
    } else if (number > UINT_MAX) 
    {
        rc = ERR_OVERFLOW;
        printf("Error: you exceeded size of unsigned int.\n");
    } else if (number >= pow(2, 20)) 
    {
        rc = ERR_TOO_BIG;
        printf("Error: program can't convert this number to binary system.\n");
    } else 
    {
        encoded_number = encode((unsigned int) number);
        printf("Result: %llu\n", encoded_number);
    }

    return rc;
}

unsigned long long int dec_to_bin(unsigned int number) 
{
    unsigned long long int bin_number = 0;
    unsigned long long int bit = 1;

    while (number) 
    {
        bin_number += bit * ((unsigned long long int) number % 2);
        bit *= 10;
        number /= 2;
    }

    return bin_number;
}

unsigned int get_even_bits(unsigned int number) 
{
    return ((number & 2863311530)) >> 1;
}

unsigned int get_odd_bits(unsigned int number) 
{
    return (number & 1431655765) << 1;
}

unsigned long long int encode(unsigned int number) 
{
    unsigned int odd_bits = get_odd_bits(number), even_bits = get_even_bits(number);
    unsigned long long int encoded_number = dec_to_bin((unsigned long long int) (odd_bits + even_bits));

    return encoded_number;
}
 
