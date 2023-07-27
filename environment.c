#include "main.h"

/**
 * length - get length of a path
 * @path: point to path
 * Return: length of path
 */

int length(char *path)
{
	int i, count;

	count = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '=' || path[i] == ':')
			count++;
		i++;
	}
	return (count);
}

/**
 * _environment - environment built-in print environment
 * @environment: point to environment variable
 * @arguments: point to arguments
 * Return: null
 */

void display_environmentt(char **environment, char **arguments)
{
	int i;

	for (i = 0; environment[i] != NULL; i++)
	{
		_puts(environment[i]);
		_putchar('\n');
	}
	free(arguments);
}
