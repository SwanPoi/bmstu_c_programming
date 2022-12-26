#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix_IO.h"
#include "constants.h"

void free_matrix(int **matr, int rows)
{
    for (int i = 0; i < rows; i++)
        free(matr[i]);

    free(matr);
}

int **allocate_matrix(int rows, int columns, int *code)
{
    int **matr = calloc(rows, sizeof(int *));

    if (!matr)
        *code = ERR_ALLOCATE_MATRIX;
    else
    {
        for (int i = 0; i < rows; i++)
        {
            matr[i] = calloc(columns, sizeof(int));

            if (!matr[i])
            {
                free_matrix(matr, rows);
                *code = ERR_ALLOCATE_ROW;
            }
        }
    }
    
	return matr;
}

void input_matrix(FILE *file, int **matrix, int rows, int columns)
{
	int cur = 0;
	
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			fscanf(file, "%d", &cur);
			matrix[i][j] = cur;
		}
}

int count_size(FILE *file)
{
	int size = 0;
	int cur = 0;
	
	while (!feof(file) && fscanf(file, "%d", &cur) == 1)
	{
		size++;
	}
		
		
	return (int) sqrt(size);
	
}

void print_matrix(int **matrix, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			printf("%d ", matrix[i][j]);
			
		printf("\n");
	}
}









    
