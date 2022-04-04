// 2 вариант
#include <stdio.h>

#define ERR_OK 0
#define ERR_INPUT_LENGTH 1
#define ERR_INPUT_ARRAY 2

#define N_MAX 10

size_t input_length(int *rc);
void input_array(int *array, size_t length, int *rc);
void print_array(int *array, size_t length);
void grouping_zeros(int *old_array, size_t old_length, int *new_array, size_t *new_length);
void grouping_odd(int *old_array, size_t old_length, int *new_array, size_t *new_length);
void grouping_even(int *old_array, size_t old_length, int *new_array, size_t *new_length);
void grouping(int *old_array, size_t old_length, int *new_array, size_t *new_length);

int main(void)
{
    int rc = ERR_OK;
    size_t length = input_length(&rc);

    if (rc == ERR_OK)
    {
        int array[N_MAX];
        input_array(array, length, &rc);

        if (rc == ERR_OK)
        {
            printf("Your array: ");
            print_array(array, length);

            int grouping_array[N_MAX];
            size_t grouping_length = 0;

            grouping(array, length, grouping_array, &grouping_length);

            printf("Grouping array: ");
            print_array(grouping_array, grouping_length);
        }
        else
        	printf("Error of the input of array\n");
    }
    else
    	printf("Error of the input of length\n");

    return rc;
}

size_t input_length(int *rc)
{
    int length = 0;
    if (scanf("%d", &length) != 1 || length > 10 || length < 0)
        *rc = ERR_INPUT_LENGTH;

    return (size_t)length;
}

void input_array(int *array, size_t length, int *rc)
{
    for (size_t i = 0; i < length && *rc == ERR_OK; i++)
    {
        if (scanf("%d", array + i) != 1)
            *rc = ERR_INPUT_ARRAY;
    }
}

void print_array(int *array, size_t length)
{
    for (size_t i = 0; i < length; i++)
        printf("%d ", *(array + i));
    printf("\n");
}

void grouping_zeros(int *old_array, size_t old_length, int *new_array, size_t *new_length)
{
    for (size_t i = 0; i < old_length; i++)
    {
        if (*(old_array + i) == 0)
        {
            *(new_array + (*new_length)) = 0;
            (*new_length)++;
        }
    }
}

void grouping_odd(int *old_array, size_t old_length, int *new_array, size_t *new_length)
{
    for (size_t i = 0; i < old_length; i++)
    {
        if (*(old_array + i) % 2 != 0)
        {
            *(new_array + (*new_length)) = *(old_array + i);
            (*new_length)++;
        }
    }
}

void grouping_even(int *old_array, size_t old_length, int *new_array, size_t *new_length)
{
    for (size_t i = 0; i < old_length; i++)
    {
        if (*(old_array + i) % 2 == 0 && *(old_array + i) != 0)
        {
            *(new_array + (*new_length)) = *(old_array + i);
            (*new_length)++;
        }
    }
}

void grouping(int *old_array, size_t old_length, int *new_array, size_t *new_length)
{
    grouping_even(old_array, old_length, new_array, new_length);
    grouping_odd(old_array, old_length, new_array, new_length);
    grouping_zeros(old_array, old_length, new_array, new_length);
}
