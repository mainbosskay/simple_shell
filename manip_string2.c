#include "main.h"
/**
 * string_copy - Copying a string
 * @destination: destination
 * @source: source
 * Return: pointer
 */

char *string_copy(char *destination, char *source)
{
	int j;

	j = 0;
	if (destination == source || source == 0)
		return (destination);
	while (source[j])
	{
		destination[j] = source[j];
		j++;
	}
	destination[j] = 0;
	return (destination);
}

/**
 * string_dup - Duplicating a string
 * @str: string
 * Return: pointer
 */

char *string_dup(const char *str)
{
	int len;
	char *retn;

	len = 0;
	if (!str)
		return (NULL);
	while (*str++)
		len++;
	retn = malloc(sizeof(char) * (len + 1));
	if (!retn)
		return (NULL);
	for (len++ ; len-- ;)
		retn[len] = *--str;
	return (retn);
}

/**
 * _puts - Printing input string
 * @str: string
 * Return: it is void
 */

void _puts(char *str)
{
	int j;

	j = 0;
	if (str == NULL)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - Writing the character c to standard output
 * @c: character
 * Return: either 1 if positve or -1 if negative or errno
 */

int _putchar(char c)
{
	static int j;
	static char buffer[WRITE_BUFFERSIZE];

	if (c == BUFFER_FLUSH || j >= WRITE_BUFFERSIZE)
	{
		write(1, buffer, j);
		j = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[j++] = c;
	return (1);
}

/**
 * copy_strn - Copying a string
 * @destination: destination string
 * @source: source string
 * @a: quantity of characters to be copied
 * Return: string
 */

char *copy_strn(char *destination, char *source, int a)
{
	int j;
	int d;
	char *s = destination;

	j = 0;
	while (source[j] != '\0' && j < a - 1)
	{
		destination[j] = source[j];
		j++;
	}
	if (j < a)
	{
		d = j;
		while (d < a)
		{
			destination[d] = '\0';
			d++;
		}
	}
	return (s);
}
