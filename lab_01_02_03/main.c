#include <stdio.h>
#include <math.h>

float square_of_triangle(float x, float y, float alpha);

int main(void)
{
    float a, b, alpha;
    float square;

    scanf("%f%f%f", &a, &b, &alpha);

    square = square_of_triangle(a, b, alpha);

    printf("%f\n", square);

    return 0;
}

float square_of_triangle(float x, float y, float alpha)
{
    float corner = alpha * 3.1415926 / 180;

    return 0.5*x*y*sin(corner);
}

