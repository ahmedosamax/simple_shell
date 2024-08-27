#include "shell.h"

/**
 * buff_free - free pointer
 * @p: adress to pointer to be freed
 * Return: 1 on success
 */
int buff_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
