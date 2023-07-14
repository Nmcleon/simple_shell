#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
#define MAX_PATH_LENGTH 1024

extern char **environ;

/* Function Declarations */
void display_prompt(void);
void read_command(char *command);
void parse_command(char *command, char **args);
int execute_command(char **args);
void handle_exit(void);
void handle_env(void);
void handle_setenv(char **args);
void handle_unsetenv(char **args);
void handle_cd(char **args);
void handle_alias(char **args);
void handle_logical_operators(char **args, int *result);
void handle_command_separator(char *command);
void handle_redirection(char **args);

char *get_full_path(char *command);
void expand_variables(char **args);
void get_variable_value(char *variable, char *value);
bool is_variable(char *arg);
void substitute_variable(char *arg);

#endif /* SHELL_H */
