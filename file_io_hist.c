#include "main.h"

/**
 * get_lninput - Printing a line minus the newline
 * @k: structure
 * Return: read bytes
 */

ssize_t get_lninput(psinfo_t *k)
{
	static char *buff;
	static size_t t;
	static size_t l;
	static size_t length;
	ssize_t d = 0;
	char **buff_cp = &(k->ag);
	char *s;

	_putchar(BUFFER_FLUSH);
	d = input_buffer(k, &buff, &length);
	if (d == -1)
		return (-1);
	if (length)
	{
		l = t;
		s = buff + t;

		chain_check(k, buff, &l, t, length);
		while (l < length)
		{
			if (chain_delim(k, buff, &l))
				break;
			l++;
		}
		t = l + 1;
		if (t >= length)
		{
			t = length = 0;
			k->cmd_buffer_type = CMD_NORM;
		}
		*buff_cp = s;
		return (string_len(s));
	}
	*buff_cp = buff;
	return (d);
}

/**
 * get_nxtline - gets the next line of input from STDIN
 * @k: parameter struct
 * @pointer: pointer to buffer, preallocated or NULL
 * @length: size of preallocated pointer buffer
 * Return: s
 */

int get_nxtline(psinfo_t *k, char **pointer, size_t *length)
{
	static char buff[READ_BUFFERSIZE];
	static size_t t;
	static size_t length_cp;
	size_t d;
	ssize_t sa = 0, ol = 0;
	char *s = NULL, *new_s = NULL;
	char *c;

	s = *pointer;
	if (s && length)
		ol = *length;
	if (t == length_cp)
		t = length_cp = 0;
	sa = read_buffer(k, buff, &length_cp);
	if (sa == -1 || (sa == 0 && length_cp == 0))
		return (-1);
	c = char_str(buff + t, '\n');
	d = c ? 1 + (unsigned int)(c - buff) : length_cp;
	new_s = mem_realloc(s, ol, ol ? ol + d : d + 1);
	if (!new_s)
		return (s ? free(s), -1 : -1);
	if (ol)
		concat_str(new_s, buff + t, d - t);
	else
		copy_strn(new_s, buff + t, d - t + 1);

	ol = ol + d - t;
	t = d;
	s = new_s;
	if (length)
		*length = ol;
	*pointer = s;
	return (ol);
}

/**
 * block_ctrlc - Blocking ctrl-C
 * @block_num: signal number
 * Return: it is void
 */

void block_ctrlc(__attribute__((unused))int block_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

/**
 * init_info - Initializing psinfo_t structure
 * @k: structure
 * Return: it is void
 */

void init_info(psinfo_t *k)
{
	k->ag = NULL;
	k->argv = NULL;
	k->path = NULL;
	k->argc = 0;
}

/**
 * set_field_info - Initializing psinfo_t structure
 * @k: structure
 * @agv: argument vector
 * Return: void
 */

void set_field_info(psinfo_t *k, char **agv)
{
	int t;

	t = 0;
	k->filename = agv[0];
	if (k->ag)
	{
		k->argv = tokenstr(k->ag, " \t");
		if (!k->argv)
		{
			k->argv = malloc(sizeof(char *) * 2);
			if (k->argv)
			{
				k->argv[0] = string_dup(k->ag);
				k->argv[1] = NULL;
			}
		}
		for (t = 0 ; k->argv && k->argv[t] ; t++)
			;
		k->argc = t;
		rep_alias(k);
		rep_variable(k);
	}
}

