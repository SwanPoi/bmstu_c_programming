#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/list_functions.h"
#include "../inc/constants.h"
#include "../inc/struct.h"

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

int append(node_t **result, node_t *src)
{
	int rc = ERR_OK;

	if (result)
	{
		summand_t *src_data = NULL;
		node_t *cur_part = *result;

		while (src != NULL && rc == ERR_OK)
		{
			node_t *cur_node = malloc(sizeof(node_t));

			if (cur_node)
			{
				summand_t *cur_data = malloc(sizeof(summand_t));

				if (cur_data)
				{
					src_data = src->data;
					cur_data->degree = src_data->degree;
					cur_data->multiplier = src_data->multiplier;

					src = src->next;

					cur_node->data = cur_data;
					cur_node->next = NULL;

					if (*result == NULL)
					{
						*result = cur_node;
						cur_part = *result;
					}
					else
					{
						cur_part->next = cur_node;
						cur_part = cur_part->next;
					}
				}
				else
					rc = ERR_ALLOC;
			}
			else
				rc = ERR_ALLOC;
		}
	}
	else
		rc = ERR_NULL;

	return rc;
}
