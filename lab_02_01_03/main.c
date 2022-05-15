#include <math.h>
#include <stdio.h>

#define ERR_OK 0
#define ERR_LENGTH 1
#define ERR_INPUT_ARR 2
#define ERR_NO_POSITIVE 3

#define SIZE_OF_ARRAY 10

size_t input_length(int *code);
void input_array(int *arr, size_t length, int *code);
void geometric_mean(int *arr, size_t length, int *code, double *mean);

int main(void)
{
    int rc = ERR_OK;
    size_t length = input_length(&rc);

    if (rc == ERR_OK)
    {
        int arr[SIZE_OF_ARRAY];
        input_array(arr, length, &rc);
        if (rc == ERR_OK)
        {
            double positive_mean;
            geometric_mean(arr, length, &rc, &positive_mean);
            if (rc == ERR_OK)
                printf("Geometric mean of positive elements: %lf\n", positive_mean);
        }
    }
    
    return rc;
}

size_t input_length(int *code)
{
    int length;
    printf("Input length of array: ");
    if (scanf("%d", &length) != 1 || length > SIZE_OF_ARRAY || length <= 0)
    {
        *code = ERR_LENGTH;
    }
    
    return (size_t) length;
}

void input_array(int *arr, size_t length, int *code)
{
    printf("Input array: ");
    for (size_t index = 0; index < length && *code == ERR_OK; index++)
    {
        if (scanf("%d", (arr + index)) != 1)
            *code = ERR_INPUT_ARR;
    }
}

void geometric_mean(int *arr, size_t length, int *code, double *mean)
{
    int quantity = 0, multi = 1;
    for (size_t index = 0; index < length; index++)
    {
        if (*(arr + index) > 0)
        {
            multi *= *(arr + index);
            quantity++;
        }
    }
    if (quantity == 0)
        *code = ERR_NO_POSITIVE;
    else
        *mean = pow(multi, (1.0 / quantity));
}
