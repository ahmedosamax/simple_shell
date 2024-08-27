#include "shell.h"
/**
 * in_buff - the input buffers
 * @infoo: ptr to struct inf
 * @buff: the double ptr to char
 * @l: ptr
 * Return: bytes
 */
ssize_t in_buff(inf *infoo, char **buff, size_t *l)
{
	ssize_t x = 0;
	size_t l_p = 0;

	if (!*l)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, si_handle);
#if USE_GTL
		r = getline(buf, &len_p, stdin);
#else
		x = gt_l(infoo, buff, &l_p);
#endif
		if (x > 0)
		{
			if ((*buff)[x - 1] == '\n')
			{
				(*buff)[x - 1] = '\0';
				x--;
			}
			infoo->line_flag = 1;
			rem_comm(*buff);
			b_hist_l(infoo, *buff, infoo->h_counter++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*l = x;
				infoo->cmd_buff = buff;
			}
		}
	}
	return (x);
}

/**
 * gt_in - get line
 * @infoo: pointer to struct inf
 * Return: bytes
 */
ssize_t gt_in(inf *infoo)
{
	static char *buff;
	static size_t x, y, l;
	ssize_t z = 0;
	char **buff_p = &(infoo->arg), *ptr;

	_putchar(BUFF_FL);
	z = in_buff(infoo, &buff, &l);
	if (z == -1)
		return (-1);
	if (l)
	{
		y = x;
		ptr = buff + x;

		ch_ch(infoo, buff, &y, x, l);
		while (y < l)
		{
			if (is_ch(infoo, buff, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= l)
		{
			x = l = 0;
			infoo->cmd_buff_t = CMD_N;
		}

		*buff_p = ptr;
		return (_strlen(ptr));
	}

	*buff_p = buff;
	return (z);
}

/**
 * r_bufff - reads the buff
 * @infoo: ptr to struct inf
 * @buff: array of string
 * @x: the size of array
 * Return: j
 */
ssize_t r_bufff(inf *infoo, char *buff, size_t *x)
{
	ssize_t j = 0;

	if (*x)
		return (0);
	j = read(infoo->r_fd, buff, R_BUFF_S);
	if (j >= 0)
		*x = j;
	return (j);
}

/**
 * gt_l - get the next lne
 * @infoo: parameter struct
 * @pp: add to ptr of len
 * @le: size of buffer
 * Return: ss
 */
int gt_l(inf *infoo, char **pp, size_t *le)
{
	static char buff[R_BUFF_S];
	static size_t x, l;
	size_t j;
	ssize_t z = 0, ss = 0;
	char *ptr = NULL, *nw_ptr = NULL, *ch_ptr;

	ptr = *pp;
	if (ptr && le)
		ss = *le;
	if (x == l)
		x = l = 0;

	z = r_bufff(infoo, buff, &l);
	if (z == -1 || (z == 0 && l == 0))
		return (-1);

	ch_ptr = _strchr(buff + x, '\n');
	j = ch_ptr ? 1 + (unsigned int)(ch_ptr - buff) : l;
	nw_ptr = _realloc(ptr, ss, ss ? ss + j : j + 1);
	if (!nw_ptr)
		return (ptr ? free(ptr), -1 : -1);

	if (ss)
		_strncat(nw_ptr, buff + x, j - x);
	else
		_strncpy(nw_ptr, buff + x, j - x + 1);
	ss += j - x;
	x = j;
	ptr = nw_ptr;

	if (le)
		*le = ss;
	*pp = ptr;
	return (ss);
}

/**
 * si_handle - blocks ctrl-C
 * @si_no: the signal number
 * Return: void
 */
void si_handle(__attribute__((unused))int si_no)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FL);
}
