#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern int EXIT_CODE;
extern int errno;

/* Write functions */
int _putchar(char c);
void _puts(char *s);

/* String functions */
int string_length(char *s);  /* Previously: _strlen*/
int string_compare(char *scp1, char *scp2);  /* Previously: _strcmp*/
char *string_duplicate(char *sd);  /* Previously: _strdup*/
char *string_concatenate(char *scn, char *sd);  /* Previously: _strcat*/

/* Process ID functions */
int get_process_id(void);  /* Previously: pid*/
int get_parent_process_id(void);  /* Previously: ppid*/

/* Main functions */
char *read_argument(int EXIT);
char **tokenize_string(char *lines);  /* Previously: tokenize*/
int argument_length(char *lines);  /* Previously: _argleng*/
int execute_program(char *arguments[], char *prog, char *lines, char **environment);  /* Previously: exec*/

/* Error functions */
void command_error(char *cmnd);  /* Previously: cmd_err*/
void execution_error(char *cmd);  /* Previously: exe_err*/
void permission_denied_error(char *name);  /* Previously: perm_denied*/

/* Path functions */
int get_path_size(char *pths);  /* Previously: path_size*/
char **get_path_directories(char **environment);  /* Previously: get_path*/
ssize_t get_line(char *read, ssize_t rdd, int fdd);  /* Previously: _getline*/

/* Environment functions */
void display_environment(char **environment, char **arguments);  /* Previously: _env*/

#endif
