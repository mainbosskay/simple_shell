#include "main.h"

/**
 * shell_int - Shell interactive mode
 * @k: strucrure
 * Return: either 0 or 1
 */

int shell_int(psinfo_t *k)
{
	return (isatty(STDIN_FILENO) && k->readfdes <= 2);
}

/**
 * shell_delim - Checking for delimeter
 * @c: char
 * @del: delimeter string
 * Return: either 0 or 1
 */

int shell_delim(char c, char *del)
{
	while (*del)
		if (*del++ == c)
			return (1);
	return (0);
}

/**
 * cmp_char - Checking for characters
 * @i: character
 * Return: either 0 or 1
 */

int cmp_char(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * atoi_char - Converting string to an integer
 * @s: string
 * Return: either 0 or converted number
 */

int atoi_char(char *s)
{
	int k;
	int symbol;
	int flg;
	int o;
	unsigned int reslt;

	symbol = 1;
	flg = 0;
	reslt = 0;
	for (k = 0 ; s[k] != '\0' && flg != 2 ; k++)
	{
		if (s[k] == '-')
			symbol = symbol * -1;
		if (s[k] >= '0' && s[k] <= '9')
		{
			flg = 1;
			reslt = reslt * 10;
			reslt = reslt + (s[k] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}
	if (symbol == -1)
		o = -reslt;
	else
		o = reslt;
	return (o);
}

/**
 * atoi_err - Converting string to an integer
 * @s: string
 * Return: either 0 or converted number or -1 if error
 */

int atoi_err(char *s)
{
	int k;
	unsigned long int reslt;

	k = 0;
	reslt = 0;
	if (*s == '+')
		s++;
	for (k = 0 ; s[k] != '\0' ; k++)
	{
		if (s[k] >= '0' && s[k] <= '9')
		{
			reslt = reslt * 10;
			reslt = reslt + (s[k] - '0');
			if (reslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (reslt);
}
