#include "main.h"

#define DELIM " \n\t\v\a"

/**
* argument_length - splits the result of getline into a vector of strings
* @lines: resulting string from getline
* Return: argument length
*/
int argument_length(char *lines)
{
int args = 1;
int i = 0;
int cmnd = 0;
while (lines[i] != '\0' && lines[i] != '\n')
{
if (lines[i] != ' ')
	cmnd = 1;
if (lines[i] == ' ' && lines[i + 1] != ' '
&& lines[i + 1] != '\n' && cmnd == 1)
args++;
i++;
}
return (args);
}
/**
* tokenize_string - function splits the command line input into tokens
* @lines: tokenized string
* Return: null(success)
*/
char **tokenize_string(char *lines)
{
int i = 0;
int b_size;
char **arguments;
char *token;
b_size = argument_length(lines);
arguments = malloc((b_size + 1) * sizeof(char *));
if (arguments == NULL)
{
free(arguments);
return (NULL);
}
token = strtok(lines, DELIM);
while (token != NULL && i <= b_size)
{
arguments[i] = token;
i++;
token = strtok(NULL, DELIM);
}
arguments[i] = NULL;
return (arguments);
}
