#include <stdio.h>

#define ERR_OK 0
#define ERR_EMPTY_ERR 1
#define OVERFLOW 100

#define SIZE_OF_ARRAY 10

void input_array(int *arr, size_t *length, int *code);
void selection_sort(int *arr, size_t length);
void swap(int *arr, size_t first_index, size_t second_index);
void print_array(int *arr, size_t length);

int main(void)
{
    int rc = ERR_OK;
    int arr[SIZE_OF_ARRAY];
    size_t length = SIZE_OF_ARRAY;

    input_array(arr, &length, &rc);

    if (rc != ERR_EMPTY_ERR)
    {
        selection_sort(arr, length);
        print_array(arr, length);
    }

    return rc;
}

void input_array(int *arr, size_t *length, int *code)
{
    int current_element = 0, index = 0;
    
    printf("Input array: ");
    while (scanf("%d", &current_element) == 1 && index <= SIZE_OF_ARRAY)
    {
        if (index != SIZE_OF_ARRAY)
            *(arr + index) = current_element;
        index++;
    }

    if (index == SIZE_OF_ARRAY + 1)
        *code = OVERFLOW;
    else if (index == 0)
        *code = ERR_EMPTY_ERR;
    else
        *length = index;
}

void swap(int *arr, size_t first_index, size_t second_index)
{
    int middle_var = *(arr + first_index);

    *(arr + first_index) = *(arr + second_index);
    *(arr + second_index) = middle_var;
}

void selection_sort(int *arr, size_t length)
{
    for (size_t i = 0; i < length - 1; i++)
    {
        size_t index_minimum = i;

        for (size_t j = i + 1; j < length; j++)
        {
            if (*(arr + j) < *(arr + index_minimum))
                index_minimum = j;
        }

        if (index_minimum != i)
            swap(arr, i, index_minimum);
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
