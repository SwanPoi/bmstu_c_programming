#include <stdio.h>
#include <math.h>

float count_moving(float speed, float acceleration, float time);

int main(void)
{
    float speed, acceleration, time;
    float moving;

    scanf("%f%f%f", &speed, &acceleration, &time);
    moving = count_moving(speed, acceleration, time);
    printf("%f\n", moving);

    return 0;
}

float count_moving(float speed, float acceleration, float time)
{
    return speed*time + acceleration*pow(time, 2)/2;
}

