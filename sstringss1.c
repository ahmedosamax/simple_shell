#include "shell.h"

/**
 * _strcpy - func copie string
 * @dest: array to dest
 * @src: array to sorce
 * Return: ptr to dest
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - dup str
 * @s: the  str to dup
 * Return: ptr to dub str
 */
char *_strdup(const char *s)
{
	int l = 0;
	char *rreturn;

	if (s == NULL)
		return (NULL);
	while (*s++)
		l++;
	rreturn = malloc(sizeof(char) * (l + 1));
	if (!rreturn)
		return (NULL);
	for (l++; l--;)
		rreturn[l] = *--s;
	return (rreturn);
}

/**
 *_puts - print string
 *@s: string to be printed
 * Return: void
 */
void _puts(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		_putchar(s[j]);
		j++;
	}
}

/**
 * _putchar - write char
 * @ch: input char
 * Return: on success 1
 */
int _putchar(char ch)
{
	static int j;
	static char buff[W_BUFF_S];

	if (ch == BUFF_FL || j >= W_BUFF_S)
	{
		write(1, buff, j);
		j = 0;
	}
	if (ch != BUFF_FL)
		buff[j++] = ch;
	return (1);
}
