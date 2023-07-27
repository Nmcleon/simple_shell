#include "main.h"

/**
  * length - the function name
  * @path: parameter of type char *.
  * Return: int .
 */
int length(char *path)
{
int i, count;
count = 0;
while (path[i] != '\0')
	{
if (path[i] == ' = ' || path[i] == ':')
	count++;
i++;
	}
return (count);
}

/**
  * display_environmentt - the function name
  * @environment: parameter of type char **.
  * @arguments: parameter of type char **.
  * Return: void .
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
