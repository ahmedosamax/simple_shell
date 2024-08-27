#include "shell.h"
/**
 * cl_info - func clear the info
 * @infoo: ptr to struct inf
 */
void cl_info(inf *infoo)
{
	infoo->arg = NULL;
	infoo->argv = NULL;
	infoo->p = NULL;
	infoo->argc = 0;
}

/**
 * st_info - func set the info
 * @infoo: ptr to struct inf
 * @avv: double ptr to character
 */
void st_info(inf *infoo, char **avv)
{
	int x = 0;

	infoo->f_name = avv[0];
	if (infoo->arg)
	{
		infoo->argv = strtw(infoo->arg, " \t");
		if (!infoo->argv)
		{

			infoo->argv = malloc(sizeof(char *) * 2);
			if (infoo->argv)
			{
				infoo->argv[0] = _strdup(infoo->arg);
				infoo->argv[1] = NULL;
			}
		}
		for (x = 0; infoo->argv && infoo->argv[x]; x++)
			;
		infoo->argc = x;

		rep_al(infoo);
		rep_var(infoo);
	}
}

/**
 * fr_info - func free infos
 * @infoo: ptr to inf struct
 * @al: check for true tast for all fields
 */
void fr_info(inf *infoo, int al)
{
	ffre(infoo->argv);
	infoo->argv = NULL;
	infoo->p = NULL;
	if (al)
	{
		if (!infoo->cmd_buff)
			free(infoo->arg);
		if (infoo->env)
			free_l(&(infoo->env));
		if (infoo->hist)
			free_l(&(infoo->hist));
		if (infoo->al)
			free_l(&(infoo->al));
		ffre(infoo->envi);
			infoo->envi = NULL;
		buff_free((void **)infoo->cmd_buff);
		if (infoo->r_fd > 2)
			close(infoo->r_fd);
		_putchar(BUFF_FL);
	}
}
