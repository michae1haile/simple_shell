#include "simple_shell.h"
/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer.
 * Return: 1 if freed, otherwise 0.
 */
int bfreed(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
