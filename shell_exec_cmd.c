#include "main.h"

/**
 * main_shell - Looping of the main shell
 * @k: info structure
 * @argv: argument vector
 * Return: either 0 or 1
 */

int main_shell(psinfo_t *k, char **argv)
{
	ssize_t d;
	int builtin_ret = 0;

	d = 0;
	while (d != -1 && builtin_ret != -2)
	{
		init_info(k);
		if (shell_int(k))
			_puts("$ ");
		exec_putchar(BUFFER_FLUSH);
		d = get_lninput(k);
		if (d != -1)
		{
			set_field_info(k, argv);
			builtin_ret = builtin_cmd(k);
			if (builtin_ret == -1)
				cmd_path(k);
		}
		else if (shell_int(k))
			_putchar('\n');
		free_field_info(k, 0);
	}
	create_history(k);
	free_field_info(k, 1);
	if (!shell_int(k) && k->status)
		exit(k->status);
	if (builtin_ret == -2)
	{
		if (k->error_num == -1)
			exit(k->status);
		exit(k->error_num);
	}
	return (builtin_ret);
}

/**
 * builtin_cmd - Discovering a builtin command
 * @k: info structure
 * Return: either -1, 0, 1, -2
 */

int builtin_cmd(psinfo_t *k)
{
	int j;
	int builtin_ret = -1;

	builtin_tab builtintb[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"help", help_shell},
		{"history", history_shell},
		{"setenv", set_env},
		{"unsetenv", un_setenv},
		{"cd", cd_shell},
		{"alias", alias_shell},
		{NULL, NULL}
	};

	for (j = 0 ; builtintb[j].type; j++)
		if (string_cmp(k->argv[0], builtintb[j].type) == 0)
		{
			k->ln_count++;
			builtin_ret = builtintb[j].funct(k);
			break;
		}
	return (builtin_ret);
}

/**
 * cmd_path - Discovering a command in PATH
 * @k: info strucure
 * Return: it is void
 */

void cmd_path(psinfo_t *k)
{
	char *path;
	int j;
	int l;

	path = NULL;
	k->path = k->argv[0];
	if (k->ln_flag == 1)
	{
		k->ln_count++;
		k->ln_flag = 0;
	}
	for (j = 0, l = 0 ; k->ag[j] ; j++)
		if (!shell_delim(k->ag[j], " \t\n"))
			l++;
	if (!l)
		return;

	path = find_cmd_path(k, getenv_val(k, "PATH="), k->argv[0]);
	if (path)
	{
		k->path = path;
		exec_fork(k);
	}
	else
	{
		if ((shell_int(k) || getenv_val(k, "PATH=") || k->argv[0][0] == '/')
			&& exec_cmd(k, k->argv[0]))
			exec_fork(k);
		else if (*(k->ag) != '\n')
		{
			k->status = 127;
			err_msg(k, "not found\n");
		}
	}
}

/**
 * exec_fork - Initiating a fork and exec thread for executing the command
 * @k: info structure
 * Return: it is void
 */

void exec_fork(psinfo_t *k)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(k->path, k->argv, getenv_list(k)) == -1)
		{
			free_field_info(k, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(k->status));
		if (WIFEXITED(k->status))
		{
			k->status = WEXITSTATUS(k->status);
			if (k->status == 126)
				err_msg(k, "Permission denied\n");
		}
	}
}

/**
 * exec_cmd - Checking whether a file is an executable command
 * @k: info structure
 * @path: the path to file
 * Return: either 0 or 1
 */

int exec_cmd(psinfo_t *k, char *path)
{
	struct stat j;

	(void)k;
	if (!path || stat(path, &j))
		return (0);
	if (j.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
