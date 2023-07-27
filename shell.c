#include "main.h"

#define _EOF (-1)

/*added implementation */

void display_environment(char **environment, char **arguments)
{
    int i = 0;
    while (environment[i] != NULL)
    {
        _puts(environment[i]);
        _puts("\n");
        i++;
    }
    free(arguments); /*Free the arguments array*/ 
}


/**
 * main - Main function for the main shell
 * @argc: Unused
 * @argv: Double pointer to the argument vector
 * @environment: Double pointer to the environment vector
 * Return: Exit (success)
 */
int main(__attribute__((unused)) int argc, char **argv, char **environment)
{
    char *line = NULL;
    char **arguments;
    char *prog = argv[0];
    int EXIT_CODE, input_c = 0;
    size_t n = 0;
    ssize_t rdd = 0;

    for (;;) /* Loop */
    {
        if (isatty(STDIN_FILENO)) /* Print prompt */
            _puts("$ ");
        rdd = getline(&line, &n, stdin);
        if (rdd == _EOF)
        {
            free(line);
            exit(EXIT_CODE); /* Receive status */
        }
        if (line[input_c] == '\n') /* Handling inputs */
        {
            continue;
            input_c++;
        }
        arguments = tokenize_string(line); /* Split input into array */
        if (string_compare(arguments[0], "exit") == 0)
        {
            free(line);
            free(arguments);
            return EXIT_CODE;
        }
        if (string_compare(arguments[0], "environment") == 0)
        {
            display_environment(environment, arguments);
            continue;
        }
        if (arguments != NULL)
        {
            EXIT_CODE = execute_program(arguments, prog, line, environment);
            free(arguments);
        }
    }
    free(line);
    free(arguments);
    return 0;
}
