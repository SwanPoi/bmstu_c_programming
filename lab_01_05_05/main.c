#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_NOT_NATURAL 2

unsigned int count_digit(unsigned int number);

int main(void)
{
    int number;
    int code, rc = ERR_OK;
    char tmp;

    if (((code = scanf("%d%c", &number, &tmp)) != 2 && code != -1) || (tmp != '\n'))
        rc = ERR_IO;
    
    else if (code == 2 && number < 1)
        rc = ERR_NOT_NATURAL;
    else
    {
        unsigned int length_of_number = count_digit(number);
        unsigned int digit;

        for (int i = length_of_number - 1; i >= 0; i--)
        {
            digit = number / (unsigned int) pow(10, i);
            printf("%u", digit);
            number = number % (unsigned int) pow(10, i);
        }
        printf("\n");
    }
    

    return rc;
}

unsigned int count_digit(unsigned int number)
{
    unsigned int count = 0;
    while (number > 0)
    {
        count++;
        number = number / 10;
    }

    return count;
}
 
