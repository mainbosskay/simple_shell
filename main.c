#include "main.h"

/**
 * main - Entry point to the shell
 * @ac: argument count
 * @av: argument vector
 * Return: either 0 or 1
 */

int main(int ac, char **av)
{
	psinfo_t k[] = { INIT_INFO };
	int fdes = 2;

	fdes = fdes + 3;

	if (ac == 2)
	{
		fdes = open(av[1], O_RDONLY);
		if (fdes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				exec_puts(av[0]);
				exec_puts(": 0: Can't open ");
				exec_puts(av[1]);
				exec_putchar('\n');
				exec_putchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		k->readfdes = fdes;
	}
	fill_env_list(k);
	read_history_file(k);
	main_shell(k, av);
	return (EXIT_SUCCESS);
}
