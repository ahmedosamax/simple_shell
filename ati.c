#include "shell.h"

/**
 * inter - returns true if shell is interactive mode
 * @infoo: adress
 * Return: 1 on interactive mode
 */
int inter(inf *infoo)
{
	return (isatty(STDIN_FILENO) && infoo->r_fd <= 2);
}

/**
 * is_del - checks for delimaterety
 * @ch: the char to be checked
 * @deli: the delimetered str
 * Return: 1 on success
 */
int is_del(char ch, char *deli)
{
	while (*deli)
		if (*deli++ == ch)
			return (1);
	return (0);
}

/**
 *is_abc - indecate if alphabetic or not
 *@ch: the input char
 *Return: 1 on true
 */

int is_abc(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - convert string to int
 *@str: the input str
 *Return: converted integer
 */

int _atoi(char *str)
{
	int j, s = 1, fl = 0, out;
	unsigned int res = 0;

	for (j = 0;  str[j] != '\0' && fl != 2; j++)
	{
		if (str[j] == '-')
			s *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			fl = 1;
			res *= 10;
			res += (str[j] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}

	if (s == -1)
		out = -res;
	else
		out = res;

	return (out);
}
