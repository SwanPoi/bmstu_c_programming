#include <stdio.h>

#define ERR_OK 0
#define ERR_LENGTH 1
#define ERR_INPUT_ARR 2
#define ERR_NO_POS_OR_NEG 3

#define SIZE_OF_ARRAY 10

size_t input_length(int *code);
void input_array(int *p_start, int *p_end, int *code);
void count_positive_and_negative(int *p_start, int *p_end, int *pos_count, int *neg_count);
void create_pos_array(int *p_start, int *p_end, int *pos_arr);
void create_neg_array(int *p_start, int *p_end, int *neg_arr);
void main_task(int *p_start, int *p_end, int *code, int *answer);
int min(int first, int second);
int sum_of_multiplications(int *pos_arr, int *neg_arr, int *p_end);

int main(void)
{
    int rc = ERR_OK;
    size_t length = input_length(&rc);

    if (rc == ERR_OK)
    {
        int arr[SIZE_OF_ARRAY];

        input_array(arr, arr + length, &rc);

        if (rc == ERR_OK)
        {
            int sum_of_multi;
            main_task(arr, arr + length, &rc, &sum_of_multi);

            if (rc == ERR_OK)
                printf("Answer is %d\n", sum_of_multi);
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
    return (size_t)length;
}

void input_array(int *p_start, int *p_end, int *code)
{
    printf("Input array: ");
    for (int *pa = p_start; pa < p_end && *code == ERR_OK; pa++)
    {
        if (scanf("%d", pa) != 1)
            *code = ERR_INPUT_ARR;
    }
}

void count_positive_and_negative(int *p_start, int *p_end, int *pos_count, int *neg_count)
{
    for (int *pa = p_start; pa < p_end; pa++)
    {
        if (*pa > 0)
            (*pos_count)++;
        else if (*pa < 0)
            (*neg_count)++;
    }
}

void create_neg_array(int *p_start, int *p_end, int *neg_arr)
{
    for (int *pa = p_start; pa < p_end; pa++)
    {
        if (*pa < 0)
        {
            *neg_arr = *pa;
            neg_arr++;
        }
    }
}

void create_pos_array(int *p_start, int *p_end, int *pos_arr)
{
    for (int *pa = --p_end; pa >= p_start; pa--)
    {
        if (*pa > 0)
        {
            *pos_arr = *pa;
            pos_arr++;
        }
    }
}

int min(int first, int second)
{
    int answer;
    if (first < second)
        answer = first;
    else
        answer = second;

    return answer;
}

int sum_of_multiplications(int *pos_arr, int *neg_arr, int *p_end)
{
    int sum_of_multi = 0;
    for (; pos_arr < p_end; pos_arr++, neg_arr++)
    {
        sum_of_multi += (*pos_arr) * (*neg_arr);
    }

    return sum_of_multi;
}

void main_task(int *p_start, int *p_end, int *code, int *answer)
{
    int pos_count = 0, neg_count = 0;
    int pos_arr[SIZE_OF_ARRAY];
    int neg_arr[SIZE_OF_ARRAY];

    count_positive_and_negative(p_start, p_end, &pos_count, &neg_count);

    if (pos_count != 0 && neg_count != 0)
    {
        create_neg_array(p_start, p_end, neg_arr);
        create_pos_array(p_start, p_end, pos_arr);

        *answer = sum_of_multiplications(pos_arr, neg_arr, pos_arr + min(pos_count, neg_count));
    }
    else
        *code = ERR_NO_POS_OR_NEG;
}
 
