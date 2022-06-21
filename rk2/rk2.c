/*
Задача: отсортировать главную диагональ в лексикографическом порядке.
*/

#include <stdio.h>
#include <string.h>

#define N 5

#define ERR_OK 0
#define ERR_SIZE 1
#define ERR_INPUT 2

typedef struct words_matrix
{
	char words[N][N][N];
	int size;
} matrix_t;

int input_size(int *code);
int input_matrix(matrix_t *words);
void output_matrix(matrix_t *words_matrix);
void sort_diagonal(matrix_t *words_matrix);
void swap(char *left_string, char *right_string);

int main(void)
{
	matrix_t words_matrix;
	int rc = ERR_OK;
	words_matrix.size = input_size(&rc);
	
	if (rc == ERR_OK)
	{
		rc = input_matrix(&words_matrix);	
		
		if (rc == ERR_OK)
		{
			printf("Matrix:\n");
			output_matrix(&words_matrix);
			
			sort_diagonal(&words_matrix);
			
			printf("Matrix with sorted diagonal:\n");
			output_matrix(&words_matrix);	
		}
	}
	
	return rc;
}

int input_size(int *code)
{
	int size = 0;
	
	printf("Input quantity of rows: ");
	if (scanf("%d", &size) != 1 || size < 1 || size > N)
		*code = ERR_SIZE;
		
	return size;
}

int input_matrix(matrix_t *words_matrix)
{
	int code = ERR_OK;
	
	for (int i = 0; i < words_matrix->size && code == ERR_OK; i++)
		for (int j = 0; j < words_matrix->size && code == ERR_OK; j++)
			if (scanf("%s", words_matrix->words[i][j]) != 1 || strlen(words_matrix->words[i][j]) > N)
				code = ERR_INPUT;
	
	return code;
}

void output_matrix(matrix_t *words_matrix)
{
	for (int i = 0; i < words_matrix->size; i++)
	{
		for (int j = 0; j < words_matrix->size; j++)
			printf("%s ", words_matrix->words[i][j]);
		
		printf("\n");
	}
}

void sort_diagonal(matrix_t *words_matrix)
{
	for (int i = 0; i < words_matrix->size - 1; i++)
		for (int j = i + 1; j < words_matrix->size; j++)
			if (strcmp(words_matrix->words[i][i], words_matrix->words[j][j]) > 0)
				swap(words_matrix->words[i][i], words_matrix->words[j][j]);
}

void swap(char *left_string, char *right_string)
{
	char temp[N];
	strcpy(temp, left_string);
	strcpy(left_string, right_string);
	strcpy(right_string, temp);
}
