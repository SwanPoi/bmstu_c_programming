#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/list_functions.h"

void *pop_front(node_t **head)
{
	void *front_data = NULL;

	if (head && *head)
	{
		node_t *head_node = *head;
		front_data = head_node->data;
		*head = head_node->next;
		free(head_node);
	}

	return front_data;
}

void *pop_back(node_t **head)
{
	void *back_data = NULL;

	if (head && *head)
	{
		node_t *node = *head;

		if ((*head)->next != NULL)
		{
			while (node->next->next != NULL)
				node = node->next;

			back_data = node->next->data;

			free(node->next);

			node->next = NULL;
		}
		else
		{
			back_data = node->data;
			free(node);
			*head = NULL;
		}
	}

	return back_data;
}

void append(node_t **head_a, node_t **head_b)
{
	if (head_a && head_b)
	{
		if (*head_a == NULL)
		{
			*head_a = *head_b;
		}
		else
		{
			node_t *node = *head_a;

			while (node->next != NULL)
				node = node->next;

			node->next = *head_b;
		}

		*head_b = NULL;
	}
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
	node_t *tail = NULL;

	if (head != NULL && head->next != NULL)
	{
		front_back_split(head, &tail);

		tail = sort(tail, comparator);
		head = sort(head, comparator);

		head = sorted_merge(&head, &tail, comparator);
	}

	return head;
}

void front_back_split(node_t *head, node_t **back)
{
	if (head != NULL && back != NULL)
	{
		int length = 0;
		node_t *node = head;

		while (node != NULL)
		{
			length++;
			node = node->next;
		}

		int half_length = (length % 2 == 0) ? (length / 2) : (length / 2 + 1);

		node = head;
		length = 1;

		while (length != half_length)
		{
			length++;
			node = node->next;
		}

		*back = node->next;
		node->next = NULL;
	}
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
	node_t *new_head = NULL;
	node_t *a_node = *head_a;
	node_t *b_node = *head_b;

	if (*head_a == NULL)
		new_head = *head_b;
	else if (*head_b == NULL)
		new_head = *head_a;
	else
	{
		if (comparator(a_node->data, b_node->data) <= 0)
		{
			new_head = a_node;
			a_node = a_node->next;
		}
		else
		{
			new_head = b_node;
			b_node = b_node->next;
		}
		
		new_head->next = sorted_merge(&a_node, &b_node, comparator);
	}

	*head_a = NULL;
	*head_b = NULL;
	a_node = NULL;
	b_node = NULL;

	return new_head;
}

int films_comparator(const void *first, const void *second)
{
	const film_t *first_film = first;
	const film_t *second_film = second;

	return first_film->ticket_price - second_film->ticket_price;
}


