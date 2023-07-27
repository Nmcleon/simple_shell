#include "shell.h"

/**
* handle_signal - Handle signal
* @signo: signo
* Return: Nothing
*/
void handle_signal(int signo __attribute__((unused)))
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "\n$ ", 3);
	}
	fflush(stdout);
}
/**
* checkmalloc - Check if malloc succeeded
* @str:
* Return:
*/
void checkmalloc(char *str)
{
	if (!str)
	{
		exit(1);
	}
}
int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)), char *envp[])
{
	char *pathstr, *tmp;
	static char *my_envp[100], *search_path[10];
	int i;
	int c;

/* Allocate memory for temporary strings */
	tmp = (char *)malloc(sizeof(char) * 100);
	pathstr = (char *)malloc(sizeof(char) * 256);
	checkmalloc(pathstr);
	checkmalloc(tmp);
/* Ignore SIGINT and handle it with custom function */
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_signal);
/* Copy environment variables */
	copy_envp(envp, my_envp);
/* Get the path string from environment variables */
	get_path_string(my_envp, pathstr);
/* Tokenize the path string and store in search_path */
	insert_pathstr_to_search(pathstr, search_path);

	while (1)
	{
/* Print the prompt if running in interactive mode */
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
/* Read input from the user */
		_memset(tmp, 0, 100);
		i = 0;
		while ((c = _getchar()) != EOF && c != '\n')
		{
			tmp[i++] = c;
			if (i >= 99)
			{
				break;
			}
		}
		if (c == EOF)
		{
			break;
		}
/* Process the input */
		if (tmp[0] != '\0')
		{
			static char *my_argv[100];
			fill_argv(tmp, my_argv);
			if (_strcmp(my_argv[0], "exit") == 0)
			{
				break;
			}
			free_argv(my_argv);
		}
	}
/* Free allocated memory */
	free(tmp);
	free(pathstr);
	for (i = 0; my_envp[i] != NULL; i++)
	free(my_envp[i]);
	for (i = 0; search_path[i] != NULL; i++)
	free(search_path[i]);
/* Print a new line before exiting if running in interactive mode */
	return (0);
}
