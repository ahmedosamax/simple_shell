#include "shell.h"

/**
 * my_env - func print current envi
 * @infoo: ptr to struct inf
 * Return: 0
 */
int my_env(inf *infoo)
{
	p_l_str(infoo->env);
	return (0);
}

/**
 * get_env - indecate the envi value
 * @infoo: ptr to struct inf
 * @ch: ptr to array of chars
 * Return: the envi value
 */
char *get_env(inf *infoo, const char *ch)
{
	list_str *no = infoo->env;
	char *ptr;

	while (no)
	{
		ptr = starts_with(no->s, ch);
		if (ptr && *ptr)
			return (ptr);
		no = no->next;
	}
	return (NULL);
}

/**
 * my_set_env - give a new envi variable
 * @infoo: ptr to struct inf
 * Return: 0
 */
int my_set_env(inf *infoo)
{
	if (infoo->argc != 3)
	{
		ror_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(infoo, infoo->argv[1], infoo->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unset_env - delete envi variable
 * @infoo: ptr to struct inf
 *  Return: 0
 */
int my_unset_env(inf *infoo)
{
	int x;

	if (infoo->argc == 1)
	{
		ror_puts("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= infoo->argc; x++)
		unset_env(infoo, infoo->argv[x]);

	return (0);
}

/**
 * pop_env_l - func for pop of linked list
 * @infoo: ptr to struct inf
 * Return: 0
 */
int pop_env_l(inf *infoo)
{
	list_str *nd = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		a_n_end(&nd, environ[x], 0);
	infoo->env = nd;
	return (0);
}
