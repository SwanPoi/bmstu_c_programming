#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_EPS 2
#define ERR_ABS 3

double approximate_sum(double x, double eps);

int main(void)
{
    double x, eps;
    int rc = ERR_OK;
    double approximate_summary, exact_summary, absolute_delta, relative_delta;

    if (scanf("%lf%lf", &x, &eps) != 2)
        rc = ERR_IO;
    else if (eps > 1 || eps <= 0)
        rc = ERR_EPS;
    else if (fabs(x) >= 1)
        rc = ERR_ABS;
    else
    {
        exact_summary = 1 / sqrt(1 - pow(x, 2));
        approximate_summary = approximate_sum(x, eps);
        absolute_delta = fabs(exact_summary - approximate_summary);
        relative_delta = absolute_delta / fabs(exact_summary);

        printf("%lf %lf %lf %lf\n", approximate_summary, exact_summary, absolute_delta, relative_delta);
    }

    return rc;
}

double approximate_sum(double x, double eps)
{
    int number = 1;
    double sum = 1.0, element = number * pow(x, 2) / (number + 1);

    while (element >= eps)
    {
        sum += element;
        number += 2;
        element *= number * pow(x, 2) / (number + 1);
    }

    return sum;
}
 
