#include <stdio.h>
#include <math.h>

double count_moving(double speed, double acceleration, double time);

int main(void)
{
    double speed, acceleration, time;
    double moving;

    scanf("%lf%lf%lf", &speed, &acceleration, &time);
    moving = count_moving(speed, acceleration, time);
    printf("%f\n", moving);

    return 0;
}

double count_moving(double speed, double acceleration, double time)
{
    return speed * time + acceleration * pow(time, 2) / 2;
}

