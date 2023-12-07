#include "main.h"

/**
 * free_str - freeing string of strings
 * @sa: string
 * Return: it is void
 */

void free_str(char **sa)
{
	char **s = sa;

	if (sa == NULL)
		return;
	while (*sa)
		free(*sa++);
	free(s);
}

/**
 * mem_realloc - Reallocating block of memory
 * @pointer: pointer from the old block
 * @o_size: old byte size
 * @n_size: new byte size
 * Return: the pointer
 */

void *mem_realloc(void *pointer, unsigned int o_size, unsigned int n_size)
{
	char *s;

	if (!pointer)
		return (malloc(n_size));
	if (!n_size)
		return (free(pointer), NULL);
	if (n_size == o_size)
		return (pointer);
	s = malloc(n_size);
	if (!s)
		return (NULL);
	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		s[o_size] = ((char *)pointer)[o_size];
	free(pointer);
	return (s);
}

/**
 * free_pointer - Freeing pointer and NULL address
 * @pointer: pointer to free
 * Return: either 1 or 0
 */

int free_pointer(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
