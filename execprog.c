#include "main.h"

/**
  * execute_program - the function name
  * @arguments: parameter of type char *.
  * @prog: parameter of type char *.
  * @lines: parameter of type char *.
  * @environment: parameter of type char **.
  * Return: int .
 */

int execute_program(char *arguments[], char *prog, char *lines, char **environment)
{
pid_t pid = fork();
char *command = arguments[0];
int state = 0;
int EXIT = 0;
if (pid < 0)
	{
perror(prog);
_exit(EXIT_FAILURE);
	}
else if (pid == 0)
	{
if ((execve(command, arguments, environment) == -1))
		{
execution_error(command);
free(arguments);
free(lines);
EXIT = 126;
_exit(EXIT);
		}
_exit(EXIT_SUCCESS);
	}
	/* wait for terminated children */
waitpid(pid, &state, WEXITSTATUS(state));
EXIT = WEXITSTATUS(state);
return (EXIT);
}
