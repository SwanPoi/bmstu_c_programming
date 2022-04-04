#include <stdio.h>
#include <math.h>

#define PI 3.1415926535

double square_of_triangle(double x, double y, double alpha);

int main(void)
{
    double a, b, alpha;
    double square;

    scanf("%lf%lf%lf", &a, &b, &alpha);

    square = square_of_triangle(a, b, alpha);

    printf("%f\n", square);

    return 0;
}

double square_of_triangle(double x, double y, double alpha)
{
    double corner = alpha * PI / 180.0;

    return 0.5 * x * y * sin(corner);
}

