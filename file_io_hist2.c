#include "main.h"

/**
 * fill_env_list - initializing linked list for environ variable
 * @k: structure
 * Return: it is zero
 */

int fill_env_list(psinfo_t *k)
{
	lst_t *node = NULL;
	size_t t;

	for (t = 0 ; environ[t] ; t++)
		end_node(&node, environ[t], 0);
	k->env = node;
	return (0);
}

/**
 * getenv_list - Providing the string array copy of our environ
 * @k: structure
 * Return: it is zero
 */

char **getenv_list(psinfo_t *k)
{
	if (!k->environ || k->env_changed)
	{
		k->environ = list_to_str(k->env);
		k->env_changed = 0;
	}
	return (k->environ);
}

/**
 * _unsetenv - Removing an environment variable
 * @k: Structure
 * @variable: string environ variable property
 * Return: either 0 or 1
 */

int _unsetenv(psinfo_t *k, char *variable)
{
	lst_t *node = k->env;
	size_t t = 0;
	char *s;

	if (!node || !variable)
		return (0);
	while (node)
	{
		s = strt(node->str, variable);
		if (s && *s == '=')
		{
			k->env_changed = del_node(&(k->env), t);
			t = 0;
			node = k->env;
			continue;
		}
		node = node->next;
		t++;
	}
	return (k->env_changed);
}

/**
 * _setenv - Initializing a new environ variable
 * @k: Structure
 * @variable: string environ variable property
 * @value: string environ variable value
 * Return: it is zero
 */
int _setenv(psinfo_t *k, char *variable, char *value)
{	char *buff = NULL;
	lst_t *node;
	char *s;

	if (!variable || !value)
		return (0);
	buff = malloc(string_len(variable) + string_len(value) + 2);
	if (!buff)
		return (1);
	string_copy(buff, variable);
	string_cat(buff, "=");
	string_cat(buff, value);
	node = k->env;
	while (node)
	{
		s = strt(node->str, variable);
		if (s && *s == '=')
		{
			free(node->str);
			node->str = buff;
			k->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	end_node(&(k->env), buff, 0);
	free(buff);
	k->env_changed = 1;
	return (0);
}

/**
 * file_history - Getting file history
 * @k: structure
 * Return: allocated string containg file history
 */

char *file_history(psinfo_t *k)
{
	char *buff;
	char *direc;

	direc = getenv_val(k, "HOME=");
	if (!direc)
		return (NULL);
	buff = malloc(sizeof(char) * (string_len(direc)
		+ string_len(HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	string_copy(buff, direc);
	string_cat(buff, "/");
	string_cat(buff, HISTORY_FILE);
	return (buff);
}

