#include <stdio.h>
#include "constants.h"
#include "battle.h"
#include "matrix_IO.h"


int main(int argc, char *argv[])
{
	int rc = ERR_OK;
	
	if (argc == 2)
	{
		FILE *file = fopen(argv[1], "r");
		
		if (file)
		{
			int size = count_size(file);
			
			rewind(file);
			
			int rows = size, columns = size;
			
			int **matrix = allocate_matrix(rows, columns, &rc);
			
			if (rc == ERR_OK)
			{
				input_matrix(file, matrix, rows, columns);
				
				fclose(file);
				
				print_matrix(matrix, rows, columns);
				
				battle(matrix, rows, columns);
				
				free_matrix(matrix, rows);
			}
		}
		else
			rc = ERR_OPEN;
		 
	}
	else
		rc = ERR_ARGS;
		
	return rc;
}
