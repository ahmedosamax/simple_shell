#include "shell.h"

/**
 * a_n - func add a node to list
 * @h: the head of list
 * @sttr: the info of node
 * @nnumm: index of node
 * Return: ptr to list
 */
list_str *a_n(list_str **h, const char *sttr, int nnumm)
{
	list_str *nw_h;

	if (!h)
		return (NULL);
	nw_h = malloc(sizeof(list_str));
	if (!nw_h)
		return (NULL);
	_memset((void *)nw_h, 0, sizeof(list_str));
	nw_h->n = nnumm;
	if (sttr)
	{
		nw_h->s = _strdup(sttr);
		if (!nw_h->s)
		{
			free(nw_h);
			return (NULL);
		}
	}
	nw_h->next = *h;
	*h = nw_h;
	return (nw_h);
}

/**
 * a_n_end - func add node in end
 * @h: ptr to the first element of list
 * @sttrr: info of node
 * @numm: the node index
 * Return: ptr to list
 */
list_str *a_n_end(list_str **h, const char *sttrr, int numm)
{
	list_str *nw_nd, *nd;

	if (!h)
		return (NULL);

	nd = *h;
	nw_nd = malloc(sizeof(list_str));
	if (!nw_nd)
		return (NULL);
	_memset((void *)nw_nd, 0, sizeof(list_str));
	nw_nd->n = numm;
	if (sttrr)
	{
		nw_nd->s = _strdup(sttrr);
		if (!nw_nd->s)
		{
			free(nw_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = nw_nd;
	}
	else
		*h = nw_nd;
	return (nw_nd);
}

/**
 * p_l_str - print string in the list
 * @hh: ptr to the head of list
 * Return: s of list
 */
size_t p_l_str(const list_str *hh)
{
	size_t x = 0;

	while (hh)
	{
		_puts(hh->s ? hh->s : "(nil)");
		_puts("\n");
		hh = hh->next;
		x++;
	}
	return (x);
}

/**
 * del_n_at_indx - delete node with index
 * @h: ptr to head of list
 * @inx: the index of node
 * Return: integer
 */
int del_n_at_indx(list_str **h, unsigned int inx)
{
	list_str *nd, *pr_nd;
	unsigned int x = 0;

	if (!h || !*h)
		return (0);

	if (!inx)
	{
		nd = *h;
		*h = (*h)->next;
		free(nd->s);
		free(nd);
		return (1);
	}
	nd = *h;
	while (nd)
	{
		if (x == inx)
		{
			pr_nd->next = nd->next;
			free(nd->s);
			free(nd);
			return (1);
		}
		x++;
		pr_nd = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * free_l - realloc all space in list
 * @h: ptr to head of list
 * Return: nothing
 */
void free_l(list_str **h)
{
	list_str *nd, *nx_nd, *hh;

	if (!h || !*h)
		return;
	hh = *h;
	nd = hh;
	while (nd)
	{
		nx_nd = nd->next;
		free(nd->s);
		free(nd);
		nd = nx_nd;
	}
	*h = NULL;
}
