#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLUMNS 10

#define ERR_OK 0
#define ERR_SIZE 1
#define ERR_INPUT_MATRIX 2
#define ERR_NOT_DIGIT 3
#define ERR_NO_NECESSARY_COLUMNS 4
#define ERR_EMPTY_MATRIX 5

void input_size(size_t *rows, size_t *columns, int *code);
size_t input_length(int *code, int max_length);
int input_digit(int *code);
void transform(int **matrix, int *src, size_t rows, size_t columns);
void input_matrix(int **matrix, size_t rows, size_t columns, int *code);
void output_matrix(int **matrix, size_t rows, size_t columns);
void delete_columns(int **matrix, size_t rows, size_t *columns, size_t column_number);
void find_and_delete_necessary_columns(int **matrix, size_t rows, size_t *columns, int *code, int digit);
int is_digit_in_number(int number, int standart);

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
        
        int digit = input_digit(&rc);
        
        if (rc == ERR_OK)
        {
            find_and_delete_necessary_columns(matrix, rows, &columns, &rc, digit);
            if (columns == 0)
                rc = ERR_EMPTY_MATRIX;
            else
                output_matrix(matrix, rows, columns);
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

int input_digit(int *code)
{
    int digit = -1;

    printf("Input digit: ");
    if (scanf("%d", &digit) != 1 || digit > 9 || digit < 0)
    {
        *code = ERR_NOT_DIGIT;
    }
    
    return digit;
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

void delete_columns(int **matrix, size_t rows, size_t *columns, size_t column_number)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = column_number; j < (*columns) - 1; j++)
            matrix[i][j] = matrix[i][j + 1];
    
    (*columns)--; 
}

void find_and_delete_necessary_columns(int **matrix, size_t rows, size_t *columns, int *code, int digit)
{
    size_t cur_column = 0, count_deleted_column = 0;
    while (cur_column < *columns)
    {
        int digit_in_column = 0;
        for (size_t i = 0; i < rows && digit_in_column == 0; i++)
            if (is_digit_in_number(matrix[i][cur_column], digit))
                digit_in_column = 1;
        
        if (digit_in_column)
        {
            delete_columns(matrix, rows, columns, cur_column);
            count_deleted_column++;
        }
        else
            cur_column++;
    }
    if (!count_deleted_column)
        *code = ERR_NO_NECESSARY_COLUMNS;
}

int is_digit_in_number(int number, int standart)
{
    int is_in_number = 0;
    
    if (number == standart)
        is_in_number = 1;
    else
    {
        int temporary_number = abs(number);
        
        while (temporary_number > 0 && is_in_number == 0)
        {
            if (temporary_number % 10 == standart)
                is_in_number = 1;
            
            temporary_number /= 10;
        }
    }
    
    return is_in_number;
}
