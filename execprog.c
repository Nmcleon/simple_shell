#include "main.h"

/**
 * execute_program - fork exe and wait for function
 * @arguments: pointer of tokens.
 * @prog: point to shell name
 * @lines: point to user input
 * @environment: ptr to environment vector
 * Return: integers;
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
        _exit(-EXIT_FAILURE);
    }
    else if (pid == 0) /* if child process */
    {
        if ((execve(command, arguments, environment) == -1)) /* only returns on error */
        {
            execution_error(command); /* perror if command can't execute */
            free(arguments);
            free(lines);
            _exit(-126);
        }
        _exit(EXIT_SUCCESS);
    }
    /* wait for terminated children */

    waitpid(pid, &state, WEXITSTATUS(state)); /* Return exit status of child */
    EXIT = WEXITSTATUS(state);
    return (EXIT); /* Return EXIT */
}
