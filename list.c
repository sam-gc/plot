#include <stdlib.h>
#include <stdio.h>
#include "list.h"

list_t list_list()
{
	list_t list = {NULL};
	return list;
}

void list_add(list_t *list, void *obj)
{
	node_t *head = list->head;

	for(head; head && head->right; head = head->right);

	if(!head)
	{
		head = malloc(sizeof(node_t));
		list->head = head;
		head->right = NULL;
	}
	else
	{
		head->right = malloc(sizeof(node_t));
		head = head->right;
		head->right = NULL;
	}

	head->obj = obj;
}

void list_remove_obj(list_t *list, void *obj)
{
	node_t *node = list->head;
	node_t *prev = NULL;

	for(node; node; node = node->right)
	{
		if(node->obj == obj)
		{
			if(node == list->head)
			{
				list->head = node->right;
				free(node);
				break;
			}

			prev->right = node->right;
			free(node);
			break;
		}
		prev = node;
	}
}

int list_index_of(list_t *list, void *obj)
{
	node_t *node = list->head;
	int ret = -1;
	int i;
	for(i = 0; node; node = node->right, i++)
	{
		if(node->obj == obj)
		{
			ret = i;
			break;
		}
	}

	return ret;
}

void list_remove_idx(list_t *list, int idx)
{
	node_t *node = list->head;
	node_t *prev = NULL;

	int i;
	for(i = 0; node; node = node->right, i++)
	{
		if(i == idx)
		{
			if(node == list->head)
			{
				list->head = node->right;
				free(node);
				break;
			}

			prev->right = node->right;
			free(node);
			break;
		}
	}
}

void *list_obj_at(list_t *list, int idx)
{
	node_t *node = list->head;

	int i;
	for(i = 0; node; node = node->right, i++)
	{
		if(i == idx)
			return node->obj;
	}

	return NULL;
}

void list_for_each(list_t *list, ListIter iter, voidptr data)
{
	node_t *node = list->head;

	for(node; node; node = node->right)
	{
		iter(node->obj, data);
	}
}

// void list_for_each_bool(list_t *list, BoolIter iter, voidptr data, FailedNodeFunc failed)
// {
// 	node_t *node = list->head;
// 	node_t *prev = NULL;
// 	int idx;

// 	for(idx = 0; node; node = node->right, idx++)
// 	{
// 		char result = iter(node->obj, data);
		
// 		if(!result)
// 		{
// 			failed(node->obj);
// 			list_remove_obj(list, node->obj);
// 			node = prev ? prev : list->head;
// 		}
// 		prev = node;
// 	}
// }

void list_clear_list(void *list, void *data)
{
	free(list);
}

void list_for_each_bool(list_t *list, BoolIter iter, voidptr data, FailedNodeFunc failed)
{
	list_t broken = list_list();
	node_t *node;

	for(node = list->head; node; node = node->right)
	{
		char result = iter(node->obj, data);

		if(!result)
		{
			failed(node->obj);
			list_add(&broken, node);
		}
	}

	list_for_each(&broken, list_clear_list, NULL);
}

int list_count(list_t *list)
{
	node_t *node = list->head;

	int i;
	for(node, i = 0; node; node = node->right, i++);

	return i;
}

void list_free(list_t *list)
{
	node_t *node = list->head;

	while(node)
	{
		node_t *next = node->right;
		free(node);
		node = next;
	}
}