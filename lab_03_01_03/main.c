#include <stdio.h>

#define ROWS 10
#define COLUMNS 10

#define INCREASING 100
#define DECREASING 200

#define ERR_OK 0
#define ERR_SIZE 1
#define ERR_INPUT_MATRIX 2

int is_monotonous(int *line, size_t length);
size_t input_length(int *code, int max_length);
void input_size(size_t *rows, size_t *columns, int *code);
void transform(int **matrix, int *src, size_t rows, size_t columns);
void input_matrix(int **matrix, size_t rows, size_t columns, int *code);
void checking_monotonous_rows(int **matrix, size_t rows, size_t columns, int *monotonous_array);
void print_array(int *arr, size_t length);

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
            int is_monotonous_rows[ROWS];
            
            checking_monotonous_rows(matrix, rows, columns, is_monotonous_rows);
            print_array(is_monotonous_rows, rows);
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

int is_monotonous(int *line, size_t length)
{
    size_t index = 0;
    int monotonous = 1;
    
    while (*(line + index) == *(line + index + 1) && index < length - 1)
        index++;
    
    if (index < length - 1)
    {
        int direction = INCREASING;
        if (*(line + index) > *(line + index + 1))
            direction = DECREASING;
        
        for (; index < length - 1 && monotonous == 1; index++)
            if ((direction == INCREASING && *(line + index) > *(line + index + 1))
                || (direction == DECREASING && *(line + index) < *(line + index + 1)))
                monotonous = 0;
    }
    
    return monotonous;
}

void checking_monotonous_rows(int **matrix, size_t rows, size_t columns, int *monotonous_array)
{
    for (size_t i = 0; i < rows; i++)
        if (columns == 1)
            *(monotonous_array + i) = 0;
        else
            *(monotonous_array + i) = is_monotonous(*(matrix + i), columns);
}

void print_array(int *arr, size_t length)
{
    for (size_t index = 0; index < length; index++)
    {
        printf("%d ", *(arr + index));
    }
    printf("\n");
}

