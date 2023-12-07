#include "main.h"

/**
 * char_dup - Duplicating characters
 * @s: PATH string
 * @strt: starting the index
 * @stp: stopping the index
 * Return: pointer for new buffer
 */

char *char_dup(char *s, int strt, int stp)
{
	static char buffer[1024];
	int j;
	int l;

	j = 0;
	l = 0;
	for (l = 0, j = strt ; j < stp ; j++)
		if (s[j] != ':')
			buffer[l++] = s[j];
	buffer[l] = 0;
	return (buffer);
}

/**
 * find_cmd_path - Locating the command in the PATH string
 * @k: info structure
 * @s: PATH string
 * @cmd: command to find
 * Return: NULL or path or command
 */

char *find_cmd_path(psinfo_t *k, char *s, char *cmd)
{
	int j;
	int position;
	char *path;

	j = 0;
	position = 0;
	if (s == NULL)
		return (NULL);
	if ((string_len(cmd) > 2) && strt(cmd, "./"))
	{
		if (exec_cmd(k, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!s[j] || s[j] == ':')
		{
			path = char_dup(s, position, j);
			if (!*path)
				string_cat(path, cmd);
			else
			{
				string_cat(path, "/");
				string_cat(path, cmd);
			}
			if (exec_cmd(k, path))
				return (path);
			if (!s[j])
				break;
			position = j;
		}
		j++;
	}
	return (NULL);
}

/**
 * exec_puts - Printing input string
 * @str: string printed
 * Return: it is void
 */

void exec_puts(char *str)
{
	int j;

	j = 0;
	if (str == NULL)
		return;
	while (str[j] != '\0')
	{
		exec_putchar(str[j]);
		j++;
	}
}

/**
 * exec_putchar - Writing the character c to standard error
 * @c: character to be printed
 * Return: either 1 if positive or -1 and errno if negative
 */

int exec_putchar(char c)
{
	static int j;
	static char buffer[WRITE_BUFFERSIZE];

	if (c == BUFFER_FLUSH || j >= WRITE_BUFFERSIZE)
	{
		write(2, buffer, j);
		j = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[j++] = c;
	return (1);
}

/**
 * putchar_fdes - Writing the character c to the given file descriptor
 * @c: character to bo printed
 * @fdes: file descriptor
 * Return: either 1 if positive or -1 and errno if negative
 */

int putchar_fdes(char c, int fdes)
{
	static int j;
	static char buffer[WRITE_BUFFERSIZE];

	if (c == BUFFER_FLUSH || j >= WRITE_BUFFERSIZE)
	{
		write(fdes, buffer, j);
		j = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[j++] = c;
	return (1);
}
