#include <stdlib.h>
#include <stdio.h>
#include "../inc/stack.h"
#include "../inc/errors.h"

int pop(stack_t *stack, int *data)
{
	int rc = ERR_OK;

	if (stack && data)
	{
		if (stack->head)
		{
			node_t *head_node = stack->head;
			*data = head_node->data;
			stack->head = stack->head->next;
			free(head_node);
			
			(stack->size)--;
		}
	}
	else
		rc = ERR_NULL;

	return rc;
}

int push(stack_t *stack, int data)
{
	int rc = ERR_OK;
	
	if (stack)
	{
		node_t *element = malloc(sizeof(node_t));
		
		if (element)
		{
			element->data = data;
			element->next = stack->head;
			stack->head  = element;
			(stack->size)++;
		}
		else
			rc = ERR_ALLOC_NODE;
	}
	else
		rc = ERR_NULL;

	return rc;
}

stack_t *init(int *rc)
{
	stack_t *stack = malloc(sizeof(stack_t));
	
	if (stack)
	{
		stack->head = NULL;
		stack->size = 0;
	}
	else
		*rc = ERR_ALLOC_STACK;
		
	return stack;
} 

void clear(stack_t **stack)
{
	int data = 0;
	
	if (stack != NULL)
		while ((*stack)->head != NULL)
			(void) pop(*stack, &data);
		
	free(*stack);
	*stack = NULL;
}

void print(stack_t *stack)
{
	node_t *cur_node = stack->head;
	
	while (cur_node)
	{
		
		for (int i = 0; i < cur_node->data; i++)
		{
			printf("*");
		}
		printf("\n");
		
		cur_node = cur_node->next;
	}
}
