#include "shell.h"

/**
 * **strtw - split string
 * @sttr: the string
 * @de: the output string
 * Return: apointer to string
 */

char **strtw(char *sttr, char *de)
{
	int x, y, l, n, n_w = 0;
	char **s_ptr;

	if (sttr == NULL || sttr[0] == 0)
		return (NULL);
	if (!de)
		de = " ";
	for (x = 0; sttr[x] != '\0'; x++)
		if (!is_del(sttr[x], de) && (is_del(sttr[x + 1], de) || !sttr[x + 1]))
			n_w++;

	if (n_w == 0)
		return (NULL);
	s_ptr = malloc((1 + n_w) * sizeof(char *));
	if (!s_ptr)
		return (NULL);
	for (x = 0, y = 0; y < n_w; y++)
	{
		while (is_del(sttr[x], de))
			x++;
		l = 0;
		while (!is_del(sttr[x + l], de) && sttr[x + l])
			l++;
		s_ptr[y] = malloc((l + 1) * sizeof(char));
		if (!s_ptr[y])
		{
			for (l = 0; l < y; l++)
				free(s_ptr[l]);
			free(s_ptr);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s_ptr[y][n] = sttr[x++];
		s_ptr[y][n] = 0;
	}
	s_ptr[y] = NULL;
	return (s_ptr);
}

/**
 * **strtw2 - split the string
 * @sttr: the string
 * @de: the output string
 * Return: apointer to array of strings
 */
char **strtw2(char *sttr, char de)
{
	int x, y, l, n, n_w = 0;
	char **s_ptr;

	if (sttr == NULL || sttr[0] == 0)
		return (NULL);
	for (x = 0; sttr[x] != '\0'; x++)
		if ((sttr[x] != de && sttr[x + 1] == de) ||
		    (sttr[x] != de && !sttr[x + 1]) || sttr[x + 1] == de)
			n_w++;
	if (n_w == 0)
		return (NULL);
	s_ptr = malloc((1 + n_w) * sizeof(char *));
	if (!s_ptr)
		return (NULL);
	for (x = 0, y = 0; y < n_w; y++)
	{
		while (sttr[x] == de && sttr[x] != de)
			x++;
		l = 0;
		while (sttr[x + l] != de && sttr[x + l] && sttr[x + l] != de)
			l++;
		s_ptr[y] = malloc((l + 1) * sizeof(char));
		if (!s_ptr[y])
		{
			for (l = 0; l < y; l++)
				free(s_ptr[l]);
			free(s_ptr);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s_ptr[y][n] = sttr[x++];
		s_ptr[y][n] = 0;
	}
	s_ptr[y] = NULL;
	return (s_ptr);
}
