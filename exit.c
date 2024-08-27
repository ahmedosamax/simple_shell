#include "shell.h"

/**
 **_strncpy - cp string
 *@dest: the dest of cp file
 *@src: the source of file to be cped
 *@i: number of chars to be cped
 *Return: concatenate str
 */
char *_strncpy(char *dest, char *src, int i)
{
	int x, y;
	char *tmp = dest;

	x = 0;
	while (src[x] != '\0' && x < i - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < i)
	{
		y = x;
		while (y < i)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (tmp);
}

/**
 **_strncat - conacte 2 strings
 *@dest: the dest of conacatinatins
 *@src: the source of conactinations
 *@i: the no of char to be concatenated
 *Return: string after concartenations
 */
char *_strncat(char *dest, char *src, int i)
{
	int x, y;
	char *tmp = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < i)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < i)
		dest[x] = '\0';
	return (tmp);
}

/**
 **_strchr - search for char in string
 *@str: string to be searched
 *@ch: the character we were looking for
 *Return: (s) pointer to area
 */
char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
