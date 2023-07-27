#include "main.h"

/**
 * command_error - function print error if command not found
 * @cmnd: pointers to caller
 * Return: 0
 */

void command_error(char *cmnd)
{

	/* Not good practice, find a way to use less sys call */
	write(STDERR_FILENO, cmnd, strlen(cmnd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, ": not found\n", 13);
}

/**
 * execution_error - return error if command cant be executed
 * @command: point command
 */

void execution_error(char *cmd)
{
	perror(cmd);
}