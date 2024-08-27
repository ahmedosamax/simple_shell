#include "shell.h"
/**
 * main - the entry point of program
 * @ac: the argv counter
 * @av: the input arg vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	inf infoo[] = { INFO_IN };
	int fdd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdd)
		: "r" (fdd));

	if (ac == 2)
	{
		fdd = open(av[1], O_RDONLY);
		if (fdd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				ror_puts(av[0]);
				ror_puts(": 0: Can't open ");
				ror_puts(av[1]);
				ror_putchar('\n');
				ror_putchar(BUFF_FL);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infoo->r_fd = fdd;
	}
	pop_env_l(infoo);
	r_hist(infoo);
	hash(infoo, av);
	return (EXIT_SUCCESS);
}
