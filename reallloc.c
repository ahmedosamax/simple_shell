#include "shell.h"

/**
 **_memset - fill the memory with buffer
 *@str: the pointer to mem
 *@ch: the char to fill mem with
 *@j: ammount of char
 *Return: pointer to the memory
 */
char *_memset(char *str, char ch, unsigned int j)
{
	unsigned int x;

	for (x = 0; x < j; x++)
		str[x] = ch;
	return (str);
}

/**
 * ffre - free string
 * @p: string contain array of strings
 */
void ffre(char **p)
{
	char **ptr = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(ptr);
}

/**
 * _realloc - simulate what realloc do
 * @pp: poitner to malloced space
 * @o_s: old size malloced
 * @n_s: new size after realloc
 * Return: pointer
*/
void *_realloc(void *pp, unsigned int o_s, unsigned int n_s)
{
	char *p;

	if (!pp)
		return (malloc(n_s));
	if (!n_s)
		return (free(pp), NULL);
	if (n_s == o_s)
		return (pp);

	p = malloc(n_s);
	if (!p)
		return (NULL);

	o_s = o_s < n_s ? o_s : n_s;
	while (o_s--)
		p[o_s] = ((char *)pp)[o_s];
	free(pp);
	return (p);
}
