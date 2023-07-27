#include "main.h"

/**
  * command_error - the function name
  * @cmnd: parameter of type char *.
  * Return: void .
 */
void command_error(char *cmnd)
{
	/* Not good practice, find a way to use less sys call */
write(STDERR_FILENO, cmnd, strlen(cmnd));
write(STDERR_FILENO, ": ", 2);
write(STDERR_FILENO, ": not found\n", 13);
}

/**
  * execution_error - the function name
  * @cmd: parameter of type char *.
  * Return: void .
 */
void execution_error(char *cmd)
{
perror(cmd);
}
