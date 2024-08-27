#include "shell.h"

/**
 * _strlen - get the length of function given
 * @s: the string to be checked
 * Return: l of string
 */
int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strcmp - compa between 2 strings
 * @s1: the first string
 * @s2: the second string
 * Return: negative or postive
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - check where the starting point
 * @hst: the string to serch
 * @dle: the substring u want to find its begin
 * Return: adress of char
 */
char *starts_with(const char *hst, const char *dle)
{
	while (*dle)
		if (*dle++ != *hst++)
			return (NULL);
	return ((char *)hst);
}

/**
 * _strcat - concate 2 strings
 * @dest: the dest buffer
 * @src: the sorce buffer
 * Return: pointer to dest array
 */
char *_strcat(char *dest, char *src)
{
	char *returrn = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (returrn);
}
