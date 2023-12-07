#include "main.h"

/**
 * chain_delim - Checking if the current char in buffer is chain delimiter
 * @k: structure
 * @buff: character buffer
 * @cp: current postion of buffer
 * Return: either 0 or 1
 */

int chain_delim(psinfo_t *k, char *buff, size_t *cp)
{
	size_t i;

	i = *cp;
	if (buff[i] == '|' && buff[i + 1] == '|')
	{
		buff[i] = 0;
		i++;
		k->cmd_buffer_type = CMD_OR;
	}
	else if (buff[i] == '&' && buff[i + 1] == '&')
	{
		buff[i] = 0;
		i++;
		k->cmd_buffer_type = CMD_AND;
	}
	else if (buff[i] == ';')
	{
		buff[i] = 0;
		k->cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*cp = i;
	return (1);
}

/**
 * chain_check - Checking if should continue chaining
 * @k: character
 * @buff: character buffer
 * @cp: current position of buffer
 * @j: starting position
 * @length: length of buffer
 * Return: it is void
 */

void chain_check(psinfo_t *k, char *buff, size_t *cp, size_t j, size_t length)
{
	size_t i;

	i = *cp;
	if (k->cmd_buffer_type == CMD_AND)
	{
		if (k->status)
		{
			buff[j] = 0;
			i = length;
		}
	}
	if (k->cmd_buffer_type == CMD_OR)
	{
		if (!k->status)
		{
			buff[j] = 0;
			i = length;
		}
	}

	*cp = i;
}

/**
 * rep_alias - Replacing an alias in token string
 * @k: structure
 * Return: either 0 or 1
 */

int rep_alias(psinfo_t *k)
{
	int i;
	lst_t *node;
	char *s;

	for (i = 0 ; i < 10 ; i++)
	{
		node = find_start_node(k->alias, k->argv[0], '=');
		if (node == NULL)
			return (0);
		free(k->argv[0]);
		s = char_str(node->str, '=');
		if (s == NULL)
			return (0);
		s = string_dup(s + 1);
		if (s == NULL)
			return (0);
		k->argv[0] = s;
	}
	return (1);
}

/**
 * rep_variable - Replacing cariable in token string
 * @k: structure
 * Return: either 0 or 1
 */

int rep_variable(psinfo_t *k)
{
	int i;
	lst_t *node;

	i = 0;
	for (i = 0; k->argv[i]; i++)
	{
		if (k->argv[i][0] != '$' || !k->argv[i][1])
			continue;
		if (!string_cmp(k->argv[i], "$?"))
		{
			rep_string(&(k->argv[i]),
				string_dup(itoa_int(k->status, 10, 0)));
			continue;
		}
		if (!string_cmp(k->argv[i], "$$"))
		{
			rep_string(&(k->argv[i]),
				string_dup(itoa_int(getpid(), 10, 0)));
			continue;
		}
		node = find_start_node(k->env, &k->argv[i][1], '=');
		if (node)
		{
			rep_string(&(k->argv[i]),
				string_dup(char_str(node->str, '=') + 1));
			continue;
		}
		rep_string(&k->argv[i], string_dup(""));

	}
	return (0);
}

/**
 * rep_string - Replacing string
 * @o: old string
 * @n: new string
 * Return: either 0 or 1
 */

int rep_string(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
