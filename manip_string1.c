#include "main.h"

/**
 * puts_fdes - Printing input string
 * @str: string
 * @fdes: file descriptor
 * Return: number of putchar
 */

int puts_fdes(char *str, int fdes)
{
	int j;

	j = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		j = j + putchar_fdes(*str++, fdes);
	}
	return (j);
}

/**
 * string_len - Returning the strings length
 * @s: string
 * Return: an integer
 */

int string_len(char *s)
{
	int j;

	j = 0;
	if (s == NULL)
		return (0);
	while (*s++)
		j++;
	return (j);
}

/**
 * string_cmp - Conducting lexicographic comparison between two strings
 * @str1: first string
 * @str2: second string
 * Return: either s < sa if negative or s > sa if positive or s == sa is zero
 */

int string_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * strt - Checking if substring starts with string
 * @str: string
 * @substr: substring
 * Return: NULL or address the next string
 */

char *strt(const char *str, const char *substr)
{
	while (*substr)
		if (*substr++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * string_cat - Concatenating two strings
 * @destination: buffers destination
 * @source: bufffers source
 * Return: pointer
 */

char *string_cat(char *destination, char *source)
{
	char *retn;

	retn = destination;
	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (retn);
}
