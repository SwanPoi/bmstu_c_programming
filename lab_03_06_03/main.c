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
void input_spiral_matrix(int **matrix, int size);
void output_matrix(int **matrix, size_t rows, size_t columns);

int main(void)
{
    int rc = ERR_OK;
    size_t rows, columns;
    
    input_size(&rows, &columns, &rc);
    
    if (rc == ERR_OK)
    {
        int src_matrix[ROWS][COLUMNS];
        int *matrix[ROWS];
        
        transform(matrix, src_matrix[0], rows, columns);
        input_spiral_matrix(matrix, (int) rows);
        
        output_matrix(matrix, rows, columns);
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

void input_spiral_matrix(int **matrix, int size)
{
    int number = 1;
    
    for (int i = 0; i < size / 2; i++)
    {
        for (int j = i; j < size - i; j++, number++)
            matrix[j][i] = number;
        
        for (int j = i + 1; j < size - i; j++, number++)
            matrix[size - i - 1][j] = number;
        
        for (int j = size - i - 2; j > i - 1; j--, number++)
            matrix[j][size - i - 1] = number;

        for (int j = size - i - 2; j > i; j--, number++)
            matrix[i][j] = number;
    }
    
    if (size % 2 != 0)
        matrix[size / 2][size / 2] = size * size;
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
