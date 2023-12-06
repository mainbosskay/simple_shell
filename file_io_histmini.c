#include "main.h"

/**
 * input_buffer - Initiating buffer chained commands
 * @k: structure
 * @buff: buffer
 * @length: length of variable
 * Return: read bytes
 */

ssize_t input_buffer(psinfo_t *k, char **buff, size_t *length)
{
	ssize_t i;
	size_t length_cp;

	i = 0;
	length_cp = 0;
	if (!*length)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, block_ctrlc);
#if USE_GETLINE
		i = get_nxtline(buff, &length_cp, stdin);
#else
		i = get_nxtline(k, buff, &length_cp);
#endif
		if (i > 0)
		{
			if ((*buff)[i - 1] == '\n')
			{
				(*buff)[i - 1] = '\0';
				i--;
			}
			k->ln_flag = 1;
			del_comms(*buff);
			add_history(k, *buff, k->history_count++);
			{
				*length = i;
				k->cmd_buffer = buff;
			}
		}
	}
	return (i);
}

/**
 * read_buffer - Reading buffer
 * @k: structure
 * @buff: buffer
 * @s: size
 * Return: sa
 */

ssize_t read_buffer(psinfo_t *k, char *buff, size_t *s)
{
	ssize_t sa;

	sa = 0;
	if (*s)
		return (0);
	sa = read(k->readfdes, buff, READ_BUFFERSIZE);
	if (sa >= 0)
		*s = sa;
	return (sa);
}
