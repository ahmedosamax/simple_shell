#include "shell.h"

/**
 * list_l - indecate l of list
 * @head: ptr to the head of list
 * Return: the s of a list
 */
size_t list_l(const list_str *head)
{
	size_t x = 0;

	while (head)
	{
		head = head->next;
		x++;
	}
	return (x);
}

/**
 * list_t_str - convert the list to string
 * @h: ptr to the head of list
 * Return: converted str
 */
char **list_t_str(list_str *h)
{
	list_str *nd = h;
	size_t x = list_l(h), z;
	char **sttrrss;
	char *sttrr;

	if (!h || !x)
		return (NULL);
	sttrrss = malloc(sizeof(char *) * (x + 1));
	if (!sttrrss)
		return (NULL);
	for (x = 0; nd; nd = nd->next, x++)
	{
		sttrr = malloc(_strlen(nd->s) + 1);
		if (!sttrr)
		{
			for (z = 0; z < x; z++)
				free(sttrrss[z]);
			free(sttrrss);
			return (NULL);
		}

		sttrr = _strcpy(sttrr, nd->s);
		sttrrss[x] = sttrr;
	}
	sttrrss[x] = NULL;
	return (sttrrss);
}


/**
 * p_list - print a single linked list
 * @head: ptr to the head of list
 * Return: s of printed list
 */
size_t p_list(const list_str *head)
{
	size_t x = 0;

	while (head)
	{
		_puts(conv_n(head->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->s ? head->s : "(nil)");
		_puts("\n");
		head = head->next;
		x++;
	}
	return (x);
}

/**
 * n_strt_w - func get where the list start
 * @nd: ptr to head of list
 * @prf: the info to search
 * @chh: the char after after prefix
 * Return: ptr to list
 */
list_str *n_strt_w(list_str *nd, char *prf, char chh)
{
	char *ptr = NULL;

	while (nd)
	{
		ptr = starts_with(nd->s, prf);
		if (ptr && ((chh == -1) || (*ptr == chh)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * gt_n_i - get the index of given node
 * @h: ptr to the head of list
 * @nd: ptr to the node we r searching for
 * Return: the index of node
 */
ssize_t gt_n_i(list_str *h, list_str *nd)
{
	size_t x = 0;

	while (h)
	{
		if (h == nd)
			return (x);
		h = h->next;
		x++;
	}
	return (-1);
}
