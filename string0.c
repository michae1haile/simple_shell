#include "shell.h"

/**
 * _strcpy - copy a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *dup;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	dup = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (dup);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1, error, -1 is returned.
 */
int _putchar(char c)
{
	static int n;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buff, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buff[n++] = c;
	return (1);
}
