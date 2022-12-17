#include <stdio.h>
#include "../inc/play.h"
#include "../inc/stack.h"
#include "../inc/errors.h"

void print_towers(stack_t *first, stack_t *second, stack_t *third)
{
	if (first && second && third)
	{
		printf("1 tower\n");
		print(first);
		printf("2 tower\n");
		print(second);
		printf("3 tower\n");
		print(third);
	}
}

int play_towers(stack_t *first_tower, stack_t *second_tower, stack_t *third_tower)
{
	int rc = ERR_OK;
	
	if (first_tower && second_tower && third_tower)
	{
		int tower_from = 0, tower_to = 0;
		int data = -1;
		
		scanf("%d%d", &tower_from, &tower_to);
		
		while (tower_from != 0 && tower_to != 0 && rc == ERR_OK && third_tower->size != MAX_SIZE)
		{
			if (tower_from == 1)
				rc = pop(first_tower, &data);
			else if (tower_from == 2)
				rc = pop(second_tower, &data);
			else if (tower_from == 3)
				rc = pop(third_tower, &data);
				
			if (data == -1)
				printf("Попытка взять диск из пустой башни\n");
			else
			{
				if (tower_to == 1)
				{
					if (first_tower->head == NULL || first_tower->head->data > data)
						rc = push(first_tower, data);
					else
					{
						printf("Нельзя установить больший диск поверх меньшего\n");
						
						if (tower_from == 1)
							rc = push(first_tower, data);
						else if (tower_from == 2)
							rc = push(second_tower, data);
						else if (tower_from == 3)
							rc = push(third_tower, data);
					}
				}
				else if (tower_to == 2)
				{
					if (second_tower->head == NULL || second_tower->head->data > data)
						rc = push(second_tower, data);
					else
					{
						printf("Нельзя установить больший диск поверх меньшего\n");
						
						if (tower_from == 1)
							rc = push(first_tower, data);
						else if (tower_from == 2)
							rc = push(second_tower, data);
						else if (tower_from == 3)
							rc = push(third_tower, data);
					}
				}
				else if (tower_to == 3)
				{
					if (third_tower->head == NULL || third_tower->head->data > data)
						rc = push(third_tower, data);
					else
					{
						printf("Нельзя установить больший диск поверх меньшего\n");
						
						if (tower_from == 1)
							rc = push(first_tower, data);
						else if (tower_from == 2)
							rc = push(second_tower, data);
						else if (tower_from == 3)
							rc = push(third_tower, data);
					}
				}
			}
			
			data = -1;
			print_towers(first_tower, second_tower, third_tower);
			
			if (third_tower->size != MAX_SIZE)
				scanf("%d%d", &tower_from, &tower_to);
		}
		
	}
	else
		rc = ERR_NULL;
	
	return rc;
}
