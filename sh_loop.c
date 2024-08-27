#include "shell.h"

/**
 * hash - the main loop of shell
 * @info: the para ret to struct
 * @av: the arg
 * Return: 0 if success
 */
int hash(inf *info, char **av)
{
	ssize_t ptr = 0;
	int bult_return = 0;

	while (ptr != -1 && bult_return != -2)
	{
		cl_info(info);
		if (inter(info))
			_puts("$ ");
		ror_putchar(BUFF_FL);
		ptr = gt_in(info);
		if (ptr != -1)
		{
			st_info(info, av);
			bult_return = fi_built(info);
			if (bult_return == -1)
				fi_cmd(info);
		}
		else if (inter(info))
			_putchar('\n');
		fr_info(info, 0);
	}
	w_hist(info);
	fr_info(info, 1);
	if (!inter(info) && info->state)
		exit(info->state);
	if (bult_return == -2)
	{
		if (info->ror_n == -1)
			exit(info->state);
		exit(info->ror_n);
	}
	return (bult_return);
}

/**
 * fi_built - indecate the builtin comand
 * @info: pointer to struct inf
 * Return: 0 on sucess
 */
int fi_built(inf *info)
{
	int x, ret_builtin = -1;
	built_t table_builtin[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_hist},
		{"setenv", my_set_env},
		{"unsetenv", my_unset_env},
		{"cd", my_cd},
		{"alias", my_al},
		{NULL, NULL}
	};

	for (x = 0; table_builtin[x].t; x++)
		if (_strcmp(info->argv[0], table_builtin[x].t) == 0)
		{
			info->line_counter++;
			ret_builtin = table_builtin[x].f(info);
			break;
		}
	return (ret_builtin);
}

/**
 * fi_cmd - find comand
 * @info: pointer to struct type inf
 * Return: void function
 */
void fi_cmd(inf *info)
{
	char *pa = NULL;
	int j, x;

	info->p = info->argv[0];
	if (info->line_flag == 1)
	{
		info->line_counter++;
		info->line_flag = 0;
	}
	for (j = 0, x = 0; info->arg[j]; j++)
		if (!is_del(info->arg[j], " \t\n"))
			x++;
	if (!x)
		return;

	pa = fi_p(info, get_env(info, "PATH="), info->argv[0]);
	if (pa)
	{
		info->p = pa;
		fo_cmd(info);
	}
	else
	{
		if ((inter(info) || get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmdd(info, info->argv[0]))
			fo_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->state = 127;
			ror_print(info, "not found\n");
		}
	}
}

/**
 * fo_cmd - fork comand
 * @info: pointer to struct type inf
 * Return: void function
 */
void fo_cmd(inf *info)
{
	pid_t ch_pd;

	ch_pd = fork();
	if (ch_pd == -1)
	{
		perror("Error:");
		return;
	}
	if (ch_pd == 0)
	{
		if (execve(info->p, info->argv, get_envi(info)) == -1)
		{
			fr_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->state));
		if (WIFEXITED(info->state))
		{
			info->state = WEXITSTATUS(info->state);
			if (info->state == 126)
				ror_print(info, "Permission denied\n");
		}
	}
}
