#include "main.h"

#define _EOF (-1)

/**
* Display the environment variables.
* @environment: Pointer to the environment variables.
* @arguments: Pointer to the command arguments.
*/
void display_environment(char **environment, char **arguments)
{
/* Implementation for displaying environment variables*/
}
/**
 * Process a single command.
 * @prog: Pointer to the name of the shell program.
 * @line: Pointer to the user input line.
 * @environment: Pointer to the environment variables.
 * Return: Exit code of the command.
 */
int process_command(char *prog, char *line, char **environment)
{
	char **arguments = tokenize_string(line);

	if (arguments == NULL)
	{
		return (-1);
	}
	int exit_code;

	if (string_compare(arguments[0], "exit") == 0)
	{
		free(arguments);
		exit_code = 0;
	}
	else if (string_compare(arguments[0], "environment") == 0)
	{
		display_environment(environment, arguments);
		exit_code = 0;
	}
	else
	{
		exit_code = execute_program(arguments, prog, line, environment);
		free(arguments);
	}
	return (exit_code);
}
/**
 * Main function for the shell.
 * @argc: Argument count.
 * @argv: Argument vector.
 * @environment: Environment variables.
 * Return: Exit code (success).
 */
int main(__attribute__((unused)) int argc, char **argv, char **environment)
{
	char *line = NULL;
	char *prog = argv[0];
	int exit_code = 0;
	size_t n = 0;
	ssize_t rdd = 0;

	for (;;)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("$ ");
		}
		rdd = getline(&line, &n, stdin);
		if (rdd == _EOF)
		{
			free(line);
			return (exit_code);
		}
		if (line[0] == '\n')
		{
			continue;
		}
		exit_code = process_command(prog, line, environment);
	}
	free(line);
	return (0);
}
