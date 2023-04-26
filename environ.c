include "simple_shell.h"

/**
 * _envir - prints the current environment
 * @info:  constant function prototype.
 * Return: 0(success)
 */
int _envir(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _envirv - function that returns the value of an environ variable
 * @info: arguments.
 * @name: env var name
 *
 * Return: the value i
 */
char *_envirv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *i;

	while (node)
	{
		i = starts_with(node->str, name);
		if (i && *i)
			return (i);
		node = node->next;
	}
	return (NULL);
}

/**
 * _envirin - function that Initialize a new environment variable.
 * @info: arguments.
 *  Return: 0 (success)
 */
int _envirin(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _envirm -function remove an environment variable
 * @info: arguments.
 * Return: 0 (success)
 */
int _envirm(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * envirpo_list - populates env linked list
 * @info: arguments.
 * Return: 0(success)
 */
int envirpo_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
