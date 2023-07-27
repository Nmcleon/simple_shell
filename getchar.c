#include "shell.h"
#ifndef BUFF_SIZE
#define BUFF_SIZE 1024
#endif
/**
 * _getchar - reads stream from stdin and stores it to a buffer.
 * Return: gives the ascii code of character read from input.
 */
int _getchar(void)
{
	static char buff[BUFF_SIZE];
	static char *chr;
	static int pos;
	static int ret;

	if (pos >= ret)
	{
		ret = read(STDIN_FILENO, buff, BUFF_SIZE);
		if (ret > 0)
		{
			chr = buff;
			pos = 0;
			return (*(chr + pos++));
		} else
			return (EOF);
	} else
		return (*(chr + pos++));
}

/**
 * remove_spaces - Removes leading spaces from the text
 * @text: input text
 * Return: Pointer to the first non-space character in the text.
 */
char *remove_spaces(char *text)
{
	while (*text == ' ')
		text++;
	return (text);
}
