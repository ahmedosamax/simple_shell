#include "shell.h"

/**
 * my_hist - display hist of file
 * @infoo: pointer to inf struct
 *  Return: integer
 */
int my_hist(inf *infoo)
{
	p_list(infoo->hist);
	return (0);
}

/**
 * un_al - st al to str
 * @infoo: ptr to inf struct
 * @s: str of al
 * Return: integer
 */
int un_al(inf *infoo, char *s)
{
	char *ptr, ch;
	int rett;

	ptr = _strchr(s, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	rett =  del_n_at_indx(&(infoo->al),
		gt_n_i(infoo->al, n_strt_w(infoo->al, s, -1)));
	*ptr = ch;
	return (rett);
}

/**
 * st_al - set alias
 * @infoo: pointer to struct inf
 * @s: str al
 * Return: integer
 */
int st_al(inf *infoo, char *s)
{
	char *ptr;

	ptr = _strchr(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (un_al(infoo, s));

	un_al(infoo, s);
	return (a_n_end(&(infoo->al), s, 0) == NULL);
}

/**
 * p_al - prints al string
 * @nd: ptr to struct list_str
 * Return: integer
 */
int p_al(list_str *nd)
{
	char *ptr = NULL, *arr = NULL;

	if (nd)
	{
		ptr = _strchr(nd->s, '=');
		for (arr = nd->s; arr <= ptr; arr++)
			_putchar(*arr);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_al - man al
 * @infoo: pointer to struct infoo
 * Return: integer
 */
int  my_al(inf *infoo)
{
	int x = 0;
	char *ptr = NULL;
	list_str *nde = NULL;

	if (infoo->argc == 1)
	{
		nde = infoo->al;
		while (nde)
		{
			p_al(nde);
			nde = nde->next;
		}
		return (0);
	}
	for (x = 1; infoo->argv[x]; x++)
	{
		ptr = _strchr(infoo->argv[x], '=');
		if (ptr)
			st_al(infoo, infoo->argv[x]);
		else
			p_al(n_strt_w(infoo->al, infoo->argv[x], '='));
	}
	return (0);
}
