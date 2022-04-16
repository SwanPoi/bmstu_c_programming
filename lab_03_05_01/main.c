#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLUMNS 10
#define SIZE_OF_ARRAY 100
#define SHIFT 3

#define ERR_OK 0
#define ERR_SIZE 1
#define ERR_INPUT_MATRIX 2
#define ERR_NO_NECESSARY_NUMBERS 3

int sum_of_digits(int number);
size_t input_length(int *code, int max_length);
void input_size(size_t *rows, size_t *columns, int *code);
void transform(int **matrix, int *src, size_t rows, size_t columns);
void input_matrix(int **matrix, size_t rows, size_t columns, int *code);
void output_matrix(int **matrix, size_t rows, size_t columns);
void form_array_of_necessary_numbers(int **matrix, size_t rows, size_t columns, 
                                     int *code, int *array, size_t *length);
void change_matrix_after_shift(int **matrix, size_t rows, size_t columns, int *array, size_t length);
void circular_shift(int *array, size_t length, size_t step);
void circular_shift_of_one_element(int *array, size_t length);

int main(void)
{
    int rc = ERR_OK;
    size_t rows, columns;
    
    input_size(&rows, &columns, &rc);
    
    if (rc == ERR_OK)
    {
        int src_matrix[ROWS][COLUMNS];
        int *matrix[ROWS];
        
        transform(matrix, &src_matrix[0][0], rows, columns);
        input_matrix(matrix, rows, columns, &rc);
        
        if (rc == ERR_OK)
        {
            int array_of_necessary_numbers[SIZE_OF_ARRAY];
            size_t length_of_array = 0;
            
            form_array_of_necessary_numbers(matrix, rows, columns, &rc, array_of_necessary_numbers, 
                &length_of_array);
            
            if (rc == ERR_OK)
            {
                circular_shift(array_of_necessary_numbers, length_of_array, SHIFT);
                change_matrix_after_shift(matrix, rows, columns, array_of_necessary_numbers, length_of_array);
                output_matrix(matrix, rows, columns);
            }
        }
    }
    
    return rc;
}

void input_size(size_t *rows, size_t *columns, int *code)
{
    *rows = input_length(code, ROWS);
    *columns = input_length(code, COLUMNS);
}    

size_t input_length(int *code, int max_length)
{
    int length = 0;

    printf("Input length: ");
    if (scanf("%d", &length) != 1 || length > max_length || length <= 0)
    {
        *code = ERR_SIZE;
    }
    
    return (size_t) length;
}

void transform(int **matrix, int *src, size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; i++)
        matrix[i] = src + i * columns;
}

void input_matrix(int **matrix, size_t rows, size_t columns, int *code)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            if (scanf("%d", (matrix[i] + j)) != 1)
                *code = ERR_INPUT_MATRIX;
}

void output_matrix(int **matrix, size_t rows, size_t columns)
{
    printf("New matrix:\n");
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void form_array_of_necessary_numbers(int **matrix, size_t rows, size_t columns, int *code, int *array, 
                                     size_t *length)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            if (sum_of_digits(matrix[i][j]) > 10)
            {
                *(array + *length) = matrix[i][j];
                (*length)++;
            }
    if (*length == 0)
        *code = ERR_NO_NECESSARY_NUMBERS;
}

void change_matrix_after_shift(int **matrix, size_t rows, size_t columns, int *array, size_t length)
{
    size_t array_index = 0;
    
    for (size_t i = 0; i < rows && array_index < length; i++)
        for (size_t j = 0; j < columns && array_index < length; j++)
            if (sum_of_digits(matrix[i][j]) > 10)
            {
                matrix[i][j] = *(array + array_index);
                array_index++;
            }
}

void circular_shift(int *array, size_t length, size_t step)
{
    if (!(length == step || length == 1))
        for (size_t i = 0; i < step; i++)
            circular_shift_of_one_element(array, length);
}

void circular_shift_of_one_element(int *array, size_t length)
{
    int first = *array;
    for (size_t i = 0; i < length - 1; i++)
        *(array + i) = *(array + i + 1);
    
    *(array + length - 1) = first;
}

int sum_of_digits(int number)
{
    int sum = 0;
    number = abs(number);
    
    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }
    
    return sum;
}
 
