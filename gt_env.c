#include "shell.h"

/**
 * get_envi - copy of string of envi
 * @infoo: ptr to struct inf
 * Return: 0
 */
char **get_envi(inf *infoo)
{
	if (!infoo->envi || infoo->env_c)
	{
		infoo->envi = list_t_str(infoo->env);
		infoo->env_c = 0;
	}

	return (infoo->envi);
}

/**
 * unset_env - delete env vairable
 * @infoo: ptr to struct inf
 * @ch: ptr to char
 * Return: 1 success
 */
int unset_env(inf *infoo, char *ch)
{
	list_str *nd = infoo->env;
	size_t x = 0;
	char *ptr;

	if (!nd || !ch)
		return (0);

	while (nd)
	{
		ptr = starts_with(nd->s, ch);
		if (ptr && *ptr == '=')
		{
			infoo->env_c = del_n_at_indx(&(infoo->env), x);
			x = 0;
			nd = infoo->env;
			continue;
		}
		nd = nd->next;
		x++;
	}
	return (infoo->env_c);
}

/**
 * set_env - set env valiable
 * @infoo: ptr to inf struct
 * @ch: ptr to char
 * @val: ptr to char
 * Return: 0
 */
int set_env(inf *infoo, char *ch, char *val)
{
	char *buff = NULL;
	list_str *nd;
	char *ptr;

	if (!ch || !val)
		return (0);

	buff = malloc(_strlen(ch) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, ch);
	_strcat(buff, "=");
	_strcat(buff, val);
	nd = infoo->env;
	while (nd)
	{
		ptr = starts_with(nd->s, ch);
		if (ptr && *ptr == '=')
		{
			free(nd->s);
			nd->s = buff;
			infoo->env_c = 1;
			return (0);
		}
		nd = nd->next;
	}
	a_n_end(&(infoo->env), buff, 0);
	free(buff);
	infoo->env_c = 1;
	return (0);
}
