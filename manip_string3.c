#include "main.h"

/**
 * concat_str - Conatenating two string
 * @destination: destination is the first string
 * @source: source is the secondd string
 * @a: maximum amount of bytes to be utilized
 * Return: concatented string
 */

char *concat_str(char *destination, char *source, int a)
{
	int j;
	int d;
	char *s = destination;

	j = 0;
	d = 0;
	while (destination[j] != '\0')
		j++;
	while (source[d] != '\0' && d < a)
	{
		destination[j] = source[d];
		j++;
		d++;
	}
	if (d < a)
		destination[j] = '\0';
	return (s);
}

/**
 * char_str - Finding a character within a string
 * @s: string
 * @c: character
 * Return: pointer
 */

char *char_str(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}

/**
 * tokenstr - Dividing a string into words, disregarding repeated delimiters
 * @str: string
 * @del: delimeter
 * Return: NULL or pointer to an array
 */
char **tokenstr(char *str, char *del)
{
	int k, t, j, d, num = 0;
	char **s;

	if (!str || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (k = 0 ; str[k] != '\0' ; k++)
		if (!shell_delim(str[k], del) && (shell_delim(str[k + 1], del)
			|| !str[k + 1]))
			num++;
	if (num == 0)
		return (NULL);
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, t = 0; t < num ; t++)
	{
		while (shell_delim(str[k], del))
			k++;
		j = 0;
		while (!shell_delim(str[k + j], del) && str[k + j])
			j++;
		s[t] = malloc((j + 1) * sizeof(char));
		if (!s[t])
		{
			for (j = 0 ; j < t ; j++)
				free(s[j]);
			free(s);
			return (NULL);
		}
		for (d = 0 ; d < j ; d++)
			s[t][d] = str[k++];
		s[t][d] = 0;
	}
	s[t] = NULL;
	return (s);
}

/**
 * strtoken - Dividing a string into words
 * @str: string
 * @del: delimeter
 * Return: NULL or pointer to an array
 */

char **strtoken(char *str, char del)
{
	int k, t, j, d, num = 0;
	char **s;

	if (!str || str[0] == 0)
		return (NULL);
	for (k = 0 ; str[k] != '\0' ; k++)
		if ((str[k] != del && str[k + 1] == del) ||
		    (str[k] != del && !str[k + 1]) || str[k + 1] == del)
			num++;
	if (num == 0)
		return (NULL);
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, t = 0 ; t < num ; t++)
	{
		while (str[k] == del && str[k] != del)
			k++;
		j = 0;
		while (str[k + j] != del && str[k + j] && str[k + j] != del)
			j++;
		s[t] = malloc((j + 1) * sizeof(char));
		if (!s[t])
		{
			for (j = 0 ; j < t ; j++)
				free(s[j]);
			free(s);
			return (NULL);
		}
		for (d = 0 ; d < j ; d++)
			s[t][d] = str[k++];
		s[t][d] = 0;
	}
	s[t] = NULL;
	return (s);
}

/**
 * set_memory - Putting memory with a constant byte
 * @s: pointer
 * @sa: byte to fil the pointer with
 * @a: number of byte
 * Return: pointer
 */

char *set_memory(char *s, char sa, unsigned int a)
{
	unsigned int k;

	for (k = 0 ; k < a ; k++)
		s[k] = sa;
	return (s);
}
