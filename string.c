#include "shell.h"

/**
 * _strlen - returns length of a string
 * @s: the string 
 * Return: (l) length of string
 */
int _strlen(char *s)
{
	int l = 0;

	if (!s)
		return (0);

	while (*s++)
		l++;
	return (l);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: (-ve) if s1 < s2, (+ve) if s1 > s2, (zero) if s1 == s2
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
 * check_start - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *check_start(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *d = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (d);
}

