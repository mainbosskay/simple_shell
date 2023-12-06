#include "main.h"

/**
 * create_history - Creating a file or appends to an existing file
 * @k: structure
 * Return: either 1 or -1
 */

int create_history(psinfo_t *k)
{
	ssize_t fdes;
	char *fname = file_history(k);
	lst_t *node = NULL;

	if (!fname)
		return (-1);
	fdes = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fdes == -1)
		return (-1);
	for (node = k->history; node; node = node->next)
	{
		puts_fdes(node->str, fdes);
		putchar_fdes('\n', fdes);
	}
	putchar_fdes(BUFFER_FLUSH, fdes);
	close(fdes);
	return (1);
}

/**
 * read_history_file - Reading file history
 * @k: structure
 * Return: either history count on success or 0
 */

int read_history_file(psinfo_t *k)
{
	int t, last = 0, lncount = 0;
	ssize_t fdes, readlen, filesize = 0;
	struct stat sa;
	char *buff = NULL, *fname = file_history(k);

	if (!fname)
		return (0);
	fdes = open(fname, O_RDONLY);
	free(fname);
	if (fdes == -1)
		return (0);
	if (!fstat(fdes, &sa))
		filesize = sa.st_size;
	if (filesize < 2)
		return (0);
	buff = malloc(sizeof(char) * (filesize + 1));
	if (!buff)
		return (0);
	readlen = read(fdes, buff, filesize);
	buff[filesize] = 0;
	if (readlen <= 0)
		return (free(buff), 0);
	close(fdes);
	for (t = 0; t < filesize; t++)
		if (buff[t] == '\n')
		{
			buff[t] = 0;
			add_history(k, buff + last, lncount++);
			last = t + 1;
		}
	if (last != t)
		add_history(k, buff + last, lncount++);
	free(buff);
	k->history_count = lncount;
	while (k->history_count-- >= HISTORY_MAX)
		del_node(&(k->history), 0);
	num_history(k);
	return (k->history_count);
}

/**
 * add_history - Adding to history linked list
 * @k: Structure
 * @buff: buffer
 * @ln_count: history linecount history count
 * Return: it is zero
 */

int add_history(psinfo_t *k, char *buff, int ln_count)
{
	lst_t *node = NULL;

	if (k->history)
		node = k->history;
	end_node(&node, buff, ln_count);
	if (!k->history)
		k->history = node;
	return (0);
}

/**
 * num_history - Renumbering history linked list after changes
 * @k: Structure
 * Return: new history count
 */

int num_history(psinfo_t *k)
{
	lst_t *node = k->history;
	int t;

	t = 0;
	while (node)
	{
		node->num = t++;
		node = node->next;
	}
	return (k->history_count = t);
}
