#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_NOT_NUMBER 1
#define ERR_EMPTY 2

void sequence(int *rc, double *sum);

int main(void)
{
    int rc = ERR_OK;
    double sum;

    sequence(&rc, &sum);
    double function = exp(sum);

    if (rc == ERR_OK)
        printf("%lf\n", function);

    return rc;
}

void sequence(int *rc, double *sum)
{
    double element, number = 0.0;
    int code;

    *sum = 1.0;
    while (((code = scanf("%lf", &element)) == 1) && element >= 0)
    {
        number += 1.0;
        *sum *= (1.0 / (element + number));
    }

    if (code != 1)
        *rc = ERR_NOT_NUMBER;
    if ((int) number == 0)
        *rc = ERR_EMPTY;
}
 
