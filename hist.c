#include "shell.h"

/**
 * gt_hist_f - get hist fl
 * @infoo: ptr to struct inf
 * Return: ptr to string
 */

char *gt_hist_f(inf *infoo)
{
	char *buff, *fl;

	fl = get_env(infoo, "HOME=");
	if (!fl)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(fl) + _strlen(HIST_F) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, fl);
	_strcat(buff, "/");
	_strcat(buff, HIST_F);
	return (buff);
}

/**
 * w_hist - create a hist file
 * @infoo: ptr to struct inf
 * Return: integer
 */
int w_hist(inf *infoo)
{
	ssize_t fdd;
	char *f_n = gt_hist_f(infoo);
	list_str *nd = NULL;

	if (!f_n)
		return (-1);

	fdd = open(f_n, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_n);
	if (fdd == -1)
		return (-1);
	for (nd = infoo->hist; nd; nd = nd->next)
	{
		ror_putsfd(nd->s, fdd);
		ror_putfd('\n', fdd);
	}
	ror_putfd(BUFF_FL, fdd);
	close(fdd);
	return (1);
}

/**
 * r_hist - read hist of file
 * @infoo: ptr to struct inf
 * Return: integer
 */
int r_hist(inf *infoo)
{
	int x, lt = 0, l_cou = 0;
	ssize_t fdd, r_d_l, f_s = 0;
	struct stat stt;
	char *buff = NULL, *fl_n = gt_hist_f(infoo);

	if (!fl_n)
		return (0);

	fdd = open(fl_n, O_RDONLY);
	free(fl_n);
	if (fdd == -1)
		return (0);
	if (!fstat(fdd, &stt))
		f_s = stt.st_size;
	if (f_s < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_s + 1));
	if (!buff)
		return (0);
	r_d_l = read(fdd, buff, f_s);
	buff[f_s] = 0;
	if (r_d_l <= 0)
		return (free(buff), 0);
	close(fdd);
	for (x = 0; x < f_s; x++)
		if (buff[x] == '\n')
		{
			buff[x] = 0;
			b_hist_l(infoo, buff + lt, l_cou++);
			lt = x + 1;
		}
	if (lt != x)
		b_hist_l(infoo, buff + lt, l_cou++);
	free(buff);
	infoo->h_counter = l_cou;
	while (infoo->h_counter-- >= HIST_M)
		del_n_at_indx(&(infoo->hist), 0);
	ren_hist(infoo);
	return (infoo->h_counter);
}

/**
 * b_hist_l - func for build a list for hist
 * @infoo: ptr for struct inf
 * @buff: a buffer
 * @l_counnt: integer conatin line counter
 * Return: integer
 */
int b_hist_l(inf *infoo, char *buff, int l_counnt)
{
	list_str *nd = NULL;

	if (infoo->hist)
		nd = infoo->hist;
	a_n_end(&nd, buff, l_counnt);

	if (!infoo->hist)
		infoo->hist = nd;
	return (0);
}

/**
 * ren_hist - renumbers the history linked list after changes
 * @infoo: ptr to struct inf
 * Return: integer
 */
int ren_hist(inf *infoo)
{
	list_str *nd = infoo->hist;
	int x = 0;

	while (nd)
	{
		nd->n = x++;
		nd = nd->next;
	}
	return (infoo->h_counter = x);
}
