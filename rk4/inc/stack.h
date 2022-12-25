#ifndef __STACK_H__
#define __STACK_H__

#define MAX_SIZE 4

typedef struct node
{
	int data;
	struct node *next;
} node_t;

typedef struct stack
{
	int size;
	node_t *head;
} stack_t;

stack_t *init(int *rc);
int pop(stack_t *stack, int *data);
int push(stack_t *stack, int data);
void clear(stack_t **stack);
void print(stack_t *stack);


#endif // __STACK_H__
