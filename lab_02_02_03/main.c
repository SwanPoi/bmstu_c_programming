#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ERR_OK 0
#define ERR_LENGTH 1
#define ERR_INPUT_ARR 2
#define ERR_EMPTY_ARR 3

#define SIZE_OF_ARRAY 10

size_t input_length(int *code);
void input_array(int *arr, size_t length, int *code);
void print_array(int *arr, size_t length);
void create_new_arr(int *arr, size_t length, int *code, int *new_arr, size_t *new_length);
int is_armstrong(int number);
size_t length_of_number(int number);

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
            int new_arr[SIZE_OF_ARRAY];
            size_t new_length = 0;

            create_new_arr(arr, length, &rc, new_arr, &new_length);
            if (rc == ERR_OK)
            {
                print_array(new_arr, new_length);
            }
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

void print_array(int *arr, size_t length)
{
    for (size_t index = 0; index < length; index++)
    {
        printf("%d ", *(arr + index));
    }
    printf("\n");
}

size_t length_of_number(int number)
{
    size_t length = 0;
    if (number == 0)
        length++;

    while (number > 0)
    {
        length++;
        number /= 10;
    }

    return length;
}

int is_armstrong(int number)
{
    int code = 0, sum_of_digits = 0;
    int draft_number = number;
    size_t length = length_of_number(abs(draft_number));

    while (draft_number > 0)
    {
        sum_of_digits += (int) pow(draft_number % 10, (int) length);
        draft_number /= 10;
    }

    if (number == sum_of_digits)
        code = 1;

    return code;
}

void create_new_arr(int *arr, size_t length, int *code, int *new_arr, size_t *new_length)
{
    for (size_t index = 0; index < length; index++)
    {
        if (is_armstrong(*(arr + index)))
        {
            *(new_arr + *new_length) = *(arr + index);
            (*new_length)++;
        }
    }
    if (*new_length == 0)
        *code = ERR_EMPTY_ARR;
}
