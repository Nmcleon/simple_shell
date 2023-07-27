#include "shell.h"

/**
* run_shell - Compiles the command to run then executes the system process
* @my_envp: environment path from os (unused)
* @search_path: tokenized paths to search through for commands (unused)
* @tmp: input from STDIN stream (unused)
*/
void run_shell(char **my_envp __attribute__((unused)),
char **search_path __attribute__((unused)), char *tmp __attribute__((unused)))
{
int i, ret;
static char *my_argv[100];
if (tmp[0] != '\0')
{
fill_argv(tmp, my_argv);
if (_strcmp(my_argv[0], "exit") == 0)
{
free_argv(my_argv);
exit(0);
}
if (attach_path(my_argv[0], search_path) == 0)
{
ret = fork();
if (ret == -1)
{
perror("Error");
}
if (ret == 0)
{
call_execve(my_argv[0], my_envp, my_argv);
perror("Error");
free_argv(my_argv);
exit(127);
}
else
{
wait(&i);
}
}
else
{
write(STDERR_FILENO, my_argv[0], _strlen(my_argv[0]));
write(STDERR_FILENO, ": not found\n", 12);
}
free_argv(my_argv);
}
}
