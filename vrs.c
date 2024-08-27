#include "shell.h"

/**
 * is_ch - func for testing file
 * @infoo: ptr to struct inf
 * @buff: buffer contain string
 * @ptr: ptr
 * Return: integer
 */
int is_ch(inf *infoo, char *buff, size_t *ptr)
{
	size_t x = *ptr;

	if (buff[x] == '|' && buff[x + 1] == '|')
	{
		buff[x] = 0;
		x++;
		infoo->cmd_buff_t = CMD_O;
	}
	else if (buff[x] == '&' && buff[x + 1] == '&')
	{
		buff[x] = 0;
		x++;
		infoo->cmd_buff_t = CMD_A;
	}
	else if (buff[x] == ';')
	{
		buff[x] = 0;
		infoo->cmd_buff_t = CMD_C;
	}
	else
		return (0);
	*ptr = x;
	return (1);
}

/**
 * ch_ch - func for checking the conitunty of chainning
 * @infoo: ptr to struct inf
 * @buff: buffer contain string
 * @ptr: pointer
 * @x: the strt pos in buffer
 * @l: the length of the buffer
 * Return: nothing
 */
void ch_ch(inf *infoo, char *buff, size_t *ptr, size_t x, size_t l)
{
	size_t z = *ptr;

	if (infoo->cmd_buff_t == CMD_A)
	{
		if (infoo->state)
		{
			buff[x] = 0;
			z = l;
		}
	}
	if (infoo->cmd_buff_t == CMD_O)
	{
		if (!infoo->state)
		{
			buff[x] = 0;
			z = l;
		}
	}

	*ptr = z;
}

/**
 * rep_al - replace aliass
 * @infoo: ptr to struct inf
 * Return: integer
 */
int rep_al(inf *infoo)
{
	int x;
	list_str *nd;
	char *ptr;

	for (x = 0; x < 10; x++)
	{
		nd = n_strt_w(infoo->al, infoo->argv[0], '=');
		if (!nd)
			return (0);
		free(infoo->argv[0]);
		ptr = _strchr(nd->s, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		infoo->argv[0] = ptr;
	}
	return (1);
}

/**
 * rep_var - func that replaces vars
 * @infoo: ptr to struct inf
 * Return: integer
 */
int rep_var(inf *infoo)
{
	int x = 0;
	list_str *nd;

	for (x = 0; infoo->argv[x]; x++)
	{
		if (infoo->argv[x][0] != '$' || !infoo->argv[x][1])
			continue;

		if (!_strcmp(infoo->argv[x], "$?"))
		{
			rep_str(&(infoo->argv[x]),
				_strdup(conv_n(infoo->state, 10, 0)));
			continue;
		}
		if (!_strcmp(infoo->argv[x], "$$"))
		{
			rep_str(&(infoo->argv[x]),
				_strdup(conv_n(getpid(), 10, 0)));
			continue;
		}
		nd = n_strt_w(infoo->env, &infoo->argv[x][1], '=');
		if (nd)
		{
			rep_str(&(infoo->argv[x]),
				_strdup(_strchr(nd->s, '=') + 1));
			continue;
		}
		rep_str(&infoo->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * rep_str - func that replace str
 * @o: double pointer to the old string
 * @nw: ptr to the new string
 * Return: integer
 */
int rep_str(char **o, char *nw)
{
	free(*o);
	*o = nw;
	return (1);
}
