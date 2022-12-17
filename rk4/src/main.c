#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/stack.h"
#include "../inc/play.h"

int main(void)
{
	int rc = ERR_OK;
	
	stack_t *first_tower = init(&rc);
	
	if (rc == ERR_OK)
	{
		stack_t *second_tower = init(&rc);
		
		if (rc == ERR_OK)
		{
			stack_t *third_tower = init(&rc);
			
			if (rc == ERR_OK)
			{
				int data = MAX_SIZE;
		
				while (rc == ERR_OK && data > 0)
				{
					rc = push(first_tower, data);
					data--;
				}
				
				print_towers(first_tower, second_tower, third_tower);
				
				rc = play_towers(first_tower, second_tower, third_tower);
				
				clear(&third_tower);
			}
			
			clear(&second_tower);
		}
		
		clear(&first_tower);
	}
}
