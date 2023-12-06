include "main.h"

/**
 * alias_unset - Unsetting alias to a string
 * @k: structure
 * @str: string alias
 * Return: either 0 or 1
 */

int alias_unset(psinfo_t *k, char *str)
{
	char *s;
	char c;
	int retn;

	s = char_str(str, '=');
	if (s == NULL)
		return (1);
	c = *s;
	*s = 0;
	retn = del_node(&(k->alias),
		get_index(k->alias, find_start_node(k->alias, str, -1)));
	*s = c;
	return (retn);
}

/**
 * alias_set - Setting alias string
 * @k:structure
 * @str: string alias
 * Return: either 0 or 1
 */

int alias_set(psinfo_t *k, char *str)
{
	char *s;

	s = char_str(str, '=');
	if (s == NULL)
		return (1);
	if (!*s++)
		return (alias_unset(k, str));
	alias_unset(k, str);
	return (end_node(&(k->alias), str, 0) == NULL);
}

/**
 * get_alias - Printing alias string
 * @node: alias node
 * Return: either 0 or 1
 */

int get_alias(lst_t *node)
{
	char *s;
	char *sa;

	s = NULL;
	sa = NULL;
	if (node)
	{
		s = char_str(node->str, '=');
		for (sa = node->str ; sa <= s ; sa++)
			_putchar(*sa);
		_putchar('\'');
		_puts(s + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_shell - Imitating the alias built-in functionality
 * @k: structure
 * Return: it is zero
 */

int alias_shell(psinfo_t *k)
{
	int j;
	char *s;
	lst_t *node;

	k = 0;
	s = NULL;
	node = NULL;
	if (k->argc == 1)
	{
		node = k->alias;
		while (node)
		{
			get_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; k->argv[j]; j++)
	{
		s = char_str(k->argv[j], '=');
		if (s)
			alias_set(k, k->argv[j]);
		else
			get_alias(find_start_node(k->alias, k->argv[j], '='));
	}

	return (0);
}
