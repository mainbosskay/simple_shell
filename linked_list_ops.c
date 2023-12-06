#include "main.h"

/**
 * start_node - Adding a node to start of the list
 * @top: pointer to head node
 * @string: string field of node
 * @num: node index used
 * Return: it is size of list
 */

lst_t *start_node(lst_t **top, const char *string, int num)
{
	lst_t *new_top;

	if (top == NULL)
		return (NULL);
	new_top = malloc(sizeof(lst_t));
	if (new_top == NULL)
		return (NULL);
	set_memory((void *)new_top, 0, sizeof(lst_t));
	new_top->num = num;
	if (string)
	{
		new_top->str = string_dup(string);
		if (!new_top->str)
		{
			free(new_top);
			return (NULL);
		}
	}
	new_top->next = *top;
	*top = new_top;
	return (new_top);
}

/**
 * end_node - Adding a node to the end
 * @top: pointer to head node
 * @string: string field of node
 * @num: node index used
 * Return: it is size of list
 */

lst_t *end_node(lst_t **top, const char *string, int num)
{
	lst_t *n_node;
	lst_t *node;

	if (!top)
		return (NULL);
	node = *top;
	n_node = malloc(sizeof(lst_t));
	if (n_node == NULL)
		return (NULL);
	set_memory((void *)n_node, 0, sizeof(lst_t));
	n_node->num = num;
	if (string)
	{
		n_node->str = string_dup(string);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = n_node;
	}
	else
		*top = n_node;
	return (n_node);
}

/**
 * print_str_list - Printing only the string element of a lst_t
 * @d: pointer to first node
 * Return: it is size of list
 */

size_t print_str_list(const lst_t *d)
{
	size_t t;

	t = 0;
	while (d)
	{
		_puts(d->str ? d->str : "(nil)");
		_puts("\n");
		d = d->next;
		t++;
	}
	return (t);
}

/**
 * del_node - Deleting node given index
 * @top: pointer to first node
 * @index: index of node to delete
 * Return: either 0 or 1
 */

int del_node(lst_t **top, unsigned int index)
{
	lst_t *node;
	lst_t *old_node;
	unsigned int t;

	t = 0;
	if (!top || !*top)
		return (0);
	if (!index)
	{
		node = *top;
		*top = (*top)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *top;
	while (node)
	{
		if (t == index)
		{
			old_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		t++;
		old_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_link_list - freeing all nodes of list
 * @top_pointer: pointer to head node
 * Return: it is void
 */

void free_link_list(lst_t **top_pointer)
{
	lst_t *node;
	lst_t *new_node;
	lst_t *top;

	if (!top_pointer || !*top_pointer)
		return;
	top = *top_pointer;
	node = top;
	while (node)
	{
		new_node = node->next;
		free(node->str);
		free(node);
		node = new_node;
	}
	*top_pointer = NULL;
}

