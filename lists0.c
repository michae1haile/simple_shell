#include "simple_shell.h"

/**
 * list_len - determines length of linked list
 * @k: pointer.
 * Return: size of list
 */
size_t list_len(const list_t *k)
{
	size_t n = 0;

	while (k)
	{
		k = k->next;
		n++;
	}
	return (n);
}

/**
 * list_to_strings - lists an array of strings.
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t n = list_len(head), k;
	char **strs;
	char *str;

	if (!head || !n)
		return (NULL);
	strs = malloc(sizeof(char *) * (n + 1));
	if (!strs)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < i; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[n] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @j: pointer to first node
  * Return: size of list
 */
size_t print_list(const list_t *j)
{
	size_t i = 0;

	while (j)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		j = j->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with -prints node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string 
 * @c: the next character after prefix 
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
