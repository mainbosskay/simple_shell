#include "main.h"

/**
 * get_listlen - Specifyingthe linked list's length
 * @d: pointer
 * Return: it is size of list
 */

size_t get_listlen(const lst_t *d)
{
	size_t t;

	t = 0;
	while (d)
	{
		d = d->next;
		t++;
	}
	return (t);
}

/**
 * list_to_str - Providing an array of strings from the list
 * @top: pointer
 * Return: it is array of strings
 */

char **list_to_str(lst_t *top)
{
	lst_t *node = top;
	size_t t;
	size_t d;
	char **strings;
	char *string;

	t = get_listlen(top);
	if (!top || !t)
		return (NULL);
	strings = malloc(sizeof(char *) * (t + 1));
	if (!strings)
		return (NULL);
	for (t = 0 ; node ; node = node->next, t++)
	{
		string = malloc(string_len(node->str) + 1);
		if (!string)
		{
			for (d = 0 ; d < t ; d++)
				free(strings[d]);
			free(strings);
			return (NULL);
		}

		string = string_copy(string, node->str);
		strings[t] = string;
	}
	strings[t] = NULL;
	return (strings);
}

/**
 * get_list - Printing all elements of a list
 * @d: pointer
 * Return: it is size of list
 */

size_t get_list(const lst_t *d)
{
	size_t t;

	t = 0;
	while (d)
	{
		_puts(itoa_int(d->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(d->str ? d->str : "(nil)");
		_puts("\n");
		d = d->next;
		t++;
	}
	return (t);
}

/**
 * find_start_node - Returning node with a string that begins with the prefix
 * @node: pointer
 * @affix: string
 * @c: character after affix
 * Return: NULL or node
 */

lst_t *find_start_node(lst_t *node, char *affix, char c)
{
	char *s = NULL;

	while (node)
	{
		s = strt(node->str, affix);
		if (s && ((c == -1) || (*s == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_index - Obtaining the index of a node
 * @top: pointer to list
 * @node: pointer to node
 * Return: either -1 or index of node
 */

size_t get_index(lst_t *top, lst_t *node)
{
	size_t t;

	t = 0;
	while (top)
	{
		if (top == node)
			return (t);
		top = top->next;
		t++;
	}
	return (-1);
}
