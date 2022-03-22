#include <stdio.h>

#define ERR_OK 0
#define ERR_LENGTH 1
#define ERR_INPUT_ARR 2

#define SIZE_OF_ARRAY 10

size_t input_length(int *code);
void input_array(int *arr, size_t length, int *code);
void print_array(int *arr, size_t length);
int reverse(int number);
void expansion_of_arr(int *arr, size_t *length, int number, size_t pos);
void arr_with_reverse(int *arr, size_t *length);

int main(void)
{
    int rc = ERR_OK;
    size_t length = input_length(&rc);

    if (rc == ERR_OK)
    {
        int arr[2 * SIZE_OF_ARRAY];
        input_array(arr, length, &rc);
        if (rc == ERR_OK)
        {
            arr_with_reverse(arr, &length);
            print_array(arr, length);
        }
    }
    
    return rc;
}

size_t input_length(int *code)
{
    int length;
    printf("Input length of array: ");
    if (scanf("%d", &length) != 1 || length > 10 || length <= 0)
    {
        *code = ERR_LENGTH;
    }
    
    return (size_t)length;
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

int reverse(int number)
{
    int new_number = 0;
    while (number > 0)
    {
        new_number = new_number * 10 + number % 10;
        number /= 10;
    }
    
    return new_number;
}

void expansion_of_arr(int *arr, size_t *length, int number, size_t pos)
{
    for (size_t index = *length; index > pos; index--)
    {
        *(arr + index) = *(arr + index - 1);
    }
    *(arr + pos) = number;
    (*length)++;
}

void arr_with_reverse(int *arr, size_t *length)
{
    size_t index = 0;
    while (index < *length)
    {
        if (*(arr + index) > 0)
        {
            expansion_of_arr(arr, length, reverse(*(arr + index)), index + 1);
            index++;
        }
        index++;
    }
}
 
