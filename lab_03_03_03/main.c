#include <stdio.h>

#define ROWS 10
#define COLUMNS 10

#define ERR_OK 0
#define ERR_SIZE 1
#define ERR_INPUT_MATRIX 2

size_t input_length(int *code, int max_length);
void input_size(size_t *rows, size_t *columns, int *code);
void transform(int **matrix, int *src, size_t rows, size_t columns);
void input_matrix(int **matrix, size_t rows, size_t columns, int *code);
void output_matrix(int **matrix, size_t rows, size_t columns);
void sort_rows(int **matrix, size_t rows, size_t columns);
void swap(int **first, int **second);
int find_min_in_row(int *row, size_t length);

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
            sort_rows(matrix, rows, columns);
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

int find_min_in_row(int *row, size_t length)
{
    int min = *(row);
    
    for (size_t i = 1; i < length; i++)
        if (*(row + i) < min)
            min = *(row + i);
        
    return min;
}

void swap(int **first, int **second)
{
    int *temporary = *first;
    *first = *second;
    *second = temporary;
}

void sort_rows(int **matrix, size_t rows, size_t columns)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < rows - i - 1; j++)
        {
            int cur = find_min_in_row(matrix[j], columns);
            int next = find_min_in_row(matrix[j + 1], columns);
            
            if (cur < next)
                swap(matrix + j, matrix + j + 1);
        }
}
 
