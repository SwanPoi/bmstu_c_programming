#include <stdio.h>

#define ROWS 10
#define COLUMNS 10

#define ERR_OK 0
#define ERR_SIZE 1
#define ERR_INPUT_MATRIX 2
#define ERR_NOT_SQUARE 3

size_t input_length(int *code, int max_length);
void input_size(size_t *rows, size_t *columns, int *code);
void transform(int **matrix, int *src, size_t rows, size_t columns);
void input_matrix(int **matrix, size_t rows, size_t columns, int *code);
void output_matrix(int **matrix, size_t rows, size_t columns);
void butterfly_sort(int **matrix, size_t rows, size_t columns);
void swap(int *first, int *second);

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
            butterfly_sort(matrix, rows, columns);
            output_matrix(matrix, rows, columns);
        }
    }
    
    return rc;
}

void input_size(size_t *rows, size_t *columns, int *code)
{
    *rows = input_length(code, ROWS);
    *columns = input_length(code, COLUMNS);
    
    if (*rows != *columns)
        *code = ERR_NOT_SQUARE;
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

void swap(int *first, int *second)
{
    int temporary = *first;
    *first = *second;
    *second = temporary;
}

 void butterfly_sort(int **matrix, size_t rows, size_t columns)
{
    size_t center = rows / 2;
    
    if (rows % 2 != 0)
        center = rows / 2 + 1;
    
    for (size_t i = 0; i < center; i++)
        for (size_t j = 0; j < i + 1; j++)
        {
            swap(matrix[i] + j, matrix[i] + (columns - j - 1));
            if (i + 1 != center || rows % 2 == 0)
                swap(matrix[rows - i - 1] + j, matrix[rows - i -1] + (columns - j -1));
        }
}
 
