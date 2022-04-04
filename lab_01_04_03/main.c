#include <stdio.h>
#include <stdlib.h>

int product_of_number(int number);

int main(void)
{
    int number;
    int product;

    scanf("%d", &number);
    product = product_of_number(abs(number));
    printf("%d\n", product);

    return 0;
}

int product_of_number(int number)
{
    int product = 1;
    
    while (number != 0)
    {
        product *= number % 10;
        number /= 10;
    }

    return product;
}
 
