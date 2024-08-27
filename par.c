#include "shell.h"
/**
 * is_cmdd - indecate the exucablity of command
 * @info: pointer to inf struct
 * @pa: path of file
 * Return: 1 on true
 */
int is_cmdd(inf *info, char *pa)
{
	struct stat stt;

	(void)info;
	if (!pa || stat(pa, &stt))
		return (0);

	if (stt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duppl_characts - dup the characters
 * @pa_str: the PATH string
 * @strt: the index from which the duplicate start
 * @stp: the index at which the dup ends
 * Return: ptr to the buffer
 */
char *duppl_characts(char *pa_str, int strt, int stp)
{
	static char buff[1024];
	int j = 0, x = 0;

	for (x = 0, j = strt; j < stp; j++)
		if (pa_str[j] != ':')
			buff[x++] = pa_str[j];
	buff[x] = 0;
	return (buff);
}

/**
 * fi_p - find the path of string
 * @info: pointer to inf struct
 * @pa_str: string pth
 * @cd: the cmd
 * Return: path of cmd
 */
char *fi_p(inf *info, char *pa_str, char *cd)
{
	int j = 0, current_post = 0;
	char *pa;

	if (!pa_str)
		return (NULL);
	if ((_strlen(cd) > 2) && starts_with(cd, "./"))
	{
		if (is_cmdd(info, cd))
			return (cd);
	}
	while (1)
	{
		if (!pa_str[j] || pa_str[j] == ':')
		{
			pa = duppl_characts(pa_str, current_post, j);
			if (!*pa)
				_strcat(pa, cd);
			else
			{
				_strcat(pa, "/");
				_strcat(pa, cd);
			}
			if (is_cmdd(info, pa))
				return (pa);
			if (!pa_str[j])
				break;
			current_post = j;
		}
		j++;
	}
	return (NULL);
}
