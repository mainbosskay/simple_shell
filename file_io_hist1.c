#include "main.h"

/**
 * free_field_info - Freeing psinfo_t structure fields
 * @k: structure
 * @all: true if freeing all fields
 * Return: it is void
 */

void free_field_info(psinfo_t *k, int all)
{
	free_str(k->argv);
	k->argv = NULL;
	k->path = NULL;
	if (all)
	{
		if (!k->cmd_buffer)
			free(k->ag);
		if (k->env)
			free_link_list(&(k->env));
		if (k->history)
			free_link_list(&(k->history));
		if (k->alias)
			free_link_list(&(k->alias));
		free_str(k->environ);
			k->environ = NULL;
		free_pointer((void **)k->cmd_buffer);
		if (k->readfdes > 2)
			close(k->readfdes);
		_putchar(BUFFER_FLUSH);
	}
}

/**
 * getenv_val - Retrieving the value of an environ variable
 * @k: structure
 * @name: variable name
 * Return: value
 */

char *getenv_val(psinfo_t *k, const char *name)
{
	lst_t *node = k->env;
	char *s;

	while (node)
	{
		s = strt(node->str, name);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}

/**
 * print_env - Printing the present environ
 * @k: structure
 * Return: it is zero
 */

int print_env(psinfo_t *k)
{
	print_str_list(k->env);
	return (0);
}

/**
 * set_env - Setting a new environ variable
 * @k: structure
 * Return: it is zero
 */

int set_env(psinfo_t *k)
{
	if (k->argc != 3)
	{
		exec_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(k, k->argv[1], k->argv[2]))
		return (0);
	return (1);
}

/**
 * un_setenv - Removing an environ variable
 * @k: structure
 * Return: it is zero
 */

int un_setenv(psinfo_t *k)
{
	int t;

	if (k->argc == 1)
	{
		exec_puts("Too few arguements.\n");
		return (1);
	}
	for (t = 1 ; t <= k->argc ; t++)
		_unsetenv(k, k->argv[t]);
	return (0);
}
