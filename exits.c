#include "simple_shell.h"
/**
 **_strncpy - copy a string
 *@dest:the destination string 
 *@src: the source string
 *@k: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int k)
{
	int m, n;
	char *d = dest;

	m = 0;
	while (src[m] != '\0' && m < k - 1)
	{
		dest[m] = src[m];
		m++;
	}
	if (m < k)
	{
		n = m;
		while (n < k)
		{
			dest[n] = '\0';
			n++;
		}
	}
	return (d);
}
/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes 
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int k)
{
	int m, n;
	char *d = dest;

	m = 0;
	n = 0;
	while (dest[m] != '\0')
		m++;
	while (src[n] != '\0' && n < k)
	{
		dest[m] = src[n];
		m++;
		n++;
	}
	if (n < k)
		dest[m] = '\0';
	return (d);
}
/**
 **_strchr - locates a character in a string
 *@s: the string 
 *@c: the character or
 *Return: (p) a pointer 
 */
char *_strchr(char *p, char c)
{
	do {
		if (*p == c)
			return (p);
	} while (*p++ != '\0');

	return (NULL);
}


