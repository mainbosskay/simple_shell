#include "main.h"

/**
 * exit_shell - Exiting shell
 * @k: structure
 * Return: 0 if k.argv[0] != exit
 */

int exit_shell(psinfo_t *k)
{
	int checkexit;

	if (k->argv[1])
	{
		checkexit = atoi_err(k->argv[1]);
		if (checkexit == -1)
		{
			k->status = 2;
			err_msg(k, "Illegal number: ");
			exec_puts(k->argv[1]);
			exec_putchar('\n');
			return (1);
		}
		k->error_num = atoi_err(k->argv[1]);
		return (-2);
	}
	k->error_num = -1;
	return (-2);
}

/**
 * cd_shell - Changing the current directory
 * @k: structure
 * Return: it is zero
 */

int cd_shell(psinfo_t *k)
{
	char *s;
	char *direc;
	char buffer[1024];
	int chgdir_ret;

	s = getcwd(buffer, 1024);
	if (s == NULL)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!k->argv[1])
	{
		direc = getenv_val(k, "HOME=");
		if (direc == NULL)
			chgdir_ret = chdir((direc = getenv_val(k, "PWD=")) ? direc : "/");
		else
			chgdir_ret = chdir(direc);
	}
	else if (string_cmp(k->argv[1], "-") == 0)
	{
		if (!getenv_val(k, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(getenv_val(k, "OLDPWD=")), _putchar('\n');
		chgdir_ret = chdir((direc = getenv_val(k, "OLDPWD=")) ? direc : "/");
	}
	else
		chgdir_ret = chdir(k->argv[1]);
	if (chgdir_ret == -1)
	{
		err_msg(k, "can't cd to ");
		exec_puts(k->argv[1]), exec_putchar('\n');
	}
	else
	{
		_setenv(k, "OLDPWD", getenv_val(k, "PWD="));
		_setenv(k, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_shell - Changing the current directory of the process
 * @k: structure
 * Return: it is zero
 */

int help_shell(psinfo_t *k)
{
	char **ag_arr;

	ag_arr = k->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ag_arr);
	return (0);
}

/**
 * history_shell - Commanding history with line numbers, starting at 0
 * @k: structure
 * Return: it is zero
 */

int history_shell(psinfo_t *k)
{
	get_list(k->history);
	return (0);
}

