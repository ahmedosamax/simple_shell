#include "shell.h"

/**
 * ror_atoi - conv str to int
 * @str: the input str
 * Return: result
 */
int ror_atoi(char *str)
{
	int j = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (j = 0;  str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			res *= 10;
			res += (str[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * ror_print - print erorr
 * @infoo: pointer to inf struct
 * @es: string of error
 * Return: nothing
 */
void ror_print(inf *infoo, char *es)
{
	ror_puts(infoo->f_name);
	ror_puts(": ");
	d_print(infoo->line_counter, STDERR_FILENO);
	ror_puts(": ");
	ror_puts(infoo->argv[0]);
	ror_puts(": ");
	ror_puts(es);
}

/**
 * d_print - func print decimal no.
 * @in: input
 * @fdd: the output
 * Return: no. of char to be printed
 */
int d_print(int in, int fdd)
{
	int (*_pr)(char) = _putchar;
	int j, counter = 0;
	unsigned int abs, curr;

	if (fdd == STDERR_FILENO)
		_pr = ror_putchar;
	if (in < 0)
	{
		abs = -in;
		_pr('-');
		counter++;
	}
	else
		abs = in;
	curr = abs;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (abs / j)
		{
			_pr('0' + curr / j);
			counter++;
		}
		curr %= j;
	}
	_pr('0' + curr);
	counter++;

	return (counter);
}

/**
 * conv_n - convert func
 * @n: a number
 * @bs: the base of number
 * @fl: argus flags
 * Return: str
 */
char *conv_n(long int n, int bs, int fl)
{
	static char *arr;
	static char buff[50];
	char s = 0;
	char *pr;
	unsigned long x = n;

	if (!(fl & CONV_UNS) && n < 0)
	{
		x = -n;
		s = '-';

	}
	arr = fl & CONV_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	pr = &buff[49];
	*pr = '\0';

	do	{
		*--pr = arr[x % bs];
		x /= bs;
	} while (x != 0);

	if (s)
		*--pr = s;
	return (pr);
}

/**
 * rem_comm - func rem comments
 * @buff: ptr to array of string
 * Return: nothing
 */
void rem_comm(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}
