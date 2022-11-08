#include <stdio.h>
#include "battle.h"

void battle(int **matrix, int rows, int columns)
{
	int cur_row = 0, cur_column = 0;
	
	get_coordinates(&cur_row, &cur_column);
	
	while (cur_column != 'q' - 'a' && cur_row >= 0)
	{
		if (is_clean(matrix, rows, columns) == 0)
		{
			printf("Victory\n");
			break;
		}	
		else if (cur_row >= rows || cur_row < 0 || cur_column  < 0 || cur_column >= columns)
			printf("0\n");
		else if (matrix[cur_row][cur_column] <= 0)
			printf("1\n");
		else if (matrix[cur_row][cur_column] > 0)
		{
			if (is_killed(matrix, rows, columns, cur_row, cur_column) == 0)
				printf("3 %d\n", matrix[cur_row][cur_column]);
			else
				printf("2 %d\n", matrix[cur_row][cur_column]);
			matrix[cur_row][cur_column] *= -1;
		}
		
		get_coordinates(&cur_row, &cur_column);
	}
}

void get_coordinates(int *row, int *column)
{
	char symbol;
	
	scanf("%c", &symbol);
	scanf("%d", row);
	
	(*row)--;
	
	(*column) = symbol - 'a';
}

int is_clean(int **matrix, int rows, int columns)
{
	int count_alive = 0;
	
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (matrix[i][j] > 0)
				count_alive++;
				
	return count_alive;			
}

int is_killed(int **matrix, int rows, int columns, int x, int y)
{
	int count_killed = 1;
	int ship = matrix[x][y];
	
	for (int i = y + 1; i < columns && i < y + ship; i++)
		if (matrix[x][i] == (-1 * ship))
			count_killed++;
			
	for (int i = y - 1; i >= 0 && i > y - ship; i--)
		if (matrix[x][i] == (-1 * ship))
			count_killed++;
			
	for (int i = x + 1; i < rows && i < x + ship; i++)
		if (matrix[i][y] == (-1 * ship))
			count_killed++;
			
	for (int i = x - 1; i >= 0 && i > x - ship; i--)
		if (matrix[i][y] == (-1 * ship))
			count_killed++;
	
	return count_killed - ship;
}
