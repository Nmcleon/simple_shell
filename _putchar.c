#include "main.h"

/**
  * _putchar - the function name
  * @c: parameter of type char .
  * Return: int .
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}

/**
  * _puts - the function name
  * @s: parameter of type char *.
  * Return: void .
 */
void _puts(char *s)
{
int i = 0;
while (s[i] != '\0')
	{
_putchar(s[i]);
i++;
	}
}
