#include "shell.h"
/**
 *ror_puts - print string
 * @s: the string
 * Return: void
 */
void ror_puts(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		ror_putchar(s[j]);
		j++;
	}
}

/**
 * ror_putchar - write character
 * @ch: the char u want to print
 * Return: 1 on success.
 */
int ror_putchar(char ch)
{
	static int j;
	static char buff[W_BUFF_S];

	if (ch == BUFF_FL || j >= W_BUFF_S)
	{
		write(2, buff, j);
		j = 0;
	}
	if (ch != BUFF_FL)
		buff[j++] = ch;
	return (1);
}

/**
 *  ror_putfd - write char to fdd
 * @ch: the char to be printed
 * @fdd: Tthe fdscoper
 * Return: 1 on sucess
 */
int ror_putfd(char ch, int fdd)
{
	static int j;
	static char buff[W_BUFF_S];

	if (ch == BUFF_FL || j >= W_BUFF_S)
	{
		write(fdd, buff, j);
		j = 0;
	}
	if (ch != BUFF_FL)
		buff[j++] = ch;
	return (1);
}

/**
 *ror_putsfd - prints an string
 * @s: the string
 * @fdd: thefd scoper
 * Return: the number of char in string
 */
int ror_putsfd(char *s, int fdd)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
	{
		j += ror_putfd(*s++, fdd);
	}
	return (j);
}
