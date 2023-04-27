#include "simple_shell.h"
/**
 * _puts - prints an input string
 * @str: the string to be printed
 * Return: void
 */
void _puts(char *str)
{
        int n = 0;

        if (!str)
                return;
        while (str[n] != '\0')
        {
                _putchar(str[n]);
                n++;
        }
}
/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int n = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[n])
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = 0;
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
	char *ptr;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	for (len++; len--;)
		ptr[len] = *--str;
	return (ptr);
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

