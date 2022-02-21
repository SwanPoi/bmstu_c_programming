#include <stdio.h>

int product_of_number(int number);

int main(void)
{
    int number;
    int product;

    scanf("%d", &number);
    product = product_of_number(number);
    printf("%d\n", product);

    return 0;
}

int product_of_number(int number)
{
    int first = number / 100;
    int last = number % 10;
    int middle = number / 10 % 10;

    return first*middle*last;
}
 
