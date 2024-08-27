#include "shell.h"

/**
 * my_exit - func for exiting the shell
 * @infoo: pointer to inf struct.
 * Return: exit with a spec status
 */
int my_exit(inf *infoo)
{
	int e_check;

	if (infoo->argv[1])
	{
		e_check = ror_atoi(infoo->argv[1]);
		if (e_check == -1)
		{
			infoo->state = 2;
			ror_print(infoo, "Illegal number: ");
			ror_puts(infoo->argv[1]);
			ror_putchar('\n');
			return (1);
		}
		infoo->ror_n = ror_atoi(infoo->argv[1]);
		return (-2);
	}
	infoo->ror_n = -1;
	return (-2);
}

/**
 * my_cd - change the dir
 * @infoo: pointer to struct inf
 * Return: integer
 */
int my_cd(inf *infoo)
{
	char *str, *ddr, buff[1024];
	int ret;

	str = getcwd(buff, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infoo->argv[1])
	{
		ddr = get_env(infoo, "HOME=");
		if (!ddr)
			ret = /* TODO: what should this be? */
				chdir((ddr = get_env(infoo, "PWD=")) ? ddr : "/");
		else
			ret = chdir(ddr);
	}
	else if (_strcmp(infoo->argv[1], "-") == 0)
	{
		if (!get_env(infoo, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(infoo, "OLDPWD=")), _putchar('\n');
		ret = chdir((ddr = get_env(infoo, "OLDPWD=")) ? ddr : "/");
	}
	else
		ret = chdir(infoo->argv[1]);
	if (ret == -1)
	{
		ror_print(infoo, "can't cd to ");
		ror_puts(infoo->argv[1]), ror_putchar('\n');
	}
	else
	{
		set_env(infoo, "OLDPWD", get_env(infoo, "PWD="));
		set_env(infoo, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * my_help - chnge dir
 * @infoo: pointer to inf struct
 *  Return: integer
 */
int my_help(inf *infoo)
{
	char **rg_arr;

	rg_arr = infoo->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*rg_arr);
	return (0);
}
