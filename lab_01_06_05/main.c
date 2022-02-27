#include <stdio.h>
#include <math.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_POINT 2
#define EPS 0.0001

double oblique_product(double x1, double y1, double x2, double y2, double x_other, double y_other);

int multiplication(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

int main(void) 
{
    int intersection, rc = ERR_OK;
    double x1, y1, x2, y2, x3, y3, x4, y4;


    if (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4) != 8)
        rc = ERR_IO;
    else if ((fabs(x1 - x2) < EPS && fabs(y1 - y2) < EPS) || (fabs(x3 - x4) < EPS && fabs(y3 - y4) < EPS))
        rc = ERR_POINT;
    else 
    {
        intersection = multiplication(x1, y1, x2, y2, x3, y3, x4, y4);

        printf("%d\n", intersection);
    }

    return rc;
}

double oblique_product(double x1, double y1, double x2, double y2, double x_other, double y_other) 
{
    return (x_other - x1) * (y2 - y1) - (y_other - y1) * (x2 - x1);
}

int multiplication(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) 
{
    int code;
    double first_multi = oblique_product(x1, y1, x2, y2, x3, y3) *
        oblique_product(x1, y1, x2, y2, x4, y4);

    double second_multi = oblique_product(x3, y3, x4, y4, x1, y1) *
        oblique_product(x3, y3, x4, y4, x2, y2);

    if (first_multi < 0 && second_multi < 0)
        code = 1;
    else
        code = 0;

    return code;
}



