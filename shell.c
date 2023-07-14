#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void display_prompt(void) {
    printf("$ ");
    fflush(stdout);
}

void read_command(char *command) {
    fgets(command, MAX_COMMAND_LENGTH, stdin);
}

void parse_command(char *command, char **args) {
    char *token;
    int i = 0;

    token = strtok(command, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

int execute_command(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        if (execvp(args[0], args) < 0) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    } else {
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}

void handle_exit(void) {
    exit(EXIT_SUCCESS);
}

void handle_env(void) {
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

void handle_setenv(char **args) {
    if (args[1] != NULL && args[2] != NULL) {
        if (setenv(args[1], args[2], 1) < 0) {
            perror("setenv");
        }
    } else {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
    }
}

void handle_unsetenv(char **args) {
    if (args[1] != NULL) {
        if (unsetenv(args[1]) < 0) {
            perror("unsetenv");
        }
    } else {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
    }
}

void handle_cd(char **args) {
    if (args[1] != NULL) {
        if (chdir(args[1]) < 0) {
            perror("chdir");
        }
    } else {
        char *home = getenv("HOME");
        if (home != NULL) {
            if (chdir(home) < 0) {
                perror("chdir");
            }
        }
    }
}

void handle_alias(char **args) {
    /* Handle the alias functionality*/
    /* Not implemented in this example*/
}

void handle_logical_operators(char **args, int *result) {
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], "&&") == 0) {
            if (*result != 0) {
                return;  /* Skip commands after && if the previous command failed*/
            }
        } else if (strcmp(args[i], "||") == 0) {
            if (*result == 0) {
                return;  /* Skip commands after || if the previous command succeeded*/
            }
        } else {
            char *trimmed_token = strtok(args[i], " \t\n");
            if (trimmed_token != NULL) {
                char *exec_args[MAX_ARGS];
                parse_command(trimmed_token, exec_args);
                *result = execute_command(exec_args);
            }
        }
        i++;
    }
}

void handle_command_separator(char *command) {
    char *token;
    char *saveptr;
    int result = 0;

    token = strtok_r(command, ";", &saveptr);
    while (token != NULL) {
        char *trimmed_token = strtok(token, " \t\n");
        if (trimmed_token != NULL) {
            char *args[MAX_ARGS];
            parse_command(trimmed_token, args);
            handle_logical_operators(args, &result);
        }
        token = strtok_r(NULL, ";", &saveptr);
    }
}

void handle_redirection(char **args) {
    int input_fd, output_fd;

    input_fd = output_fd = -1;

    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            if (args[i + 1] != NULL) {
                input_fd = open(args[i + 1], O_RDONLY);
                if (input_fd < 0) {
                    perror("open");
                } else {
                    dup2(input_fd, STDIN_FILENO);
                    close(input_fd);
                    args[i] = NULL;
                    i++;  /* Skip the file name*/
                }
            } else {
                fprintf(stderr, "Invalid usage of input redirection\n");
                return;
            }
        } else if (strcmp(args[i], ">") == 0) {
            if (args[i + 1] != NULL) {
                output_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (output_fd < 0) {
                    perror("open");
                } else {
                    dup2(output_fd, STDOUT_FILENO);
                    close(output_fd);
                    args[i] = NULL;
                    i++;  /* Skip the file name*/
                }
            } else {
                fprintf(stderr, "Invalid usage of output redirection\n");
                return;
            }
        } else if (strcmp(args[i], ">>") == 0) {
            if (args[i + 1] != NULL) {
                output_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (output_fd < 0) {
                    perror("open");
                } else {
                    dup2(output_fd, STDOUT_FILENO);
                    close(output_fd);
                    args[i] = NULL;
                    i++;  /* Skip the file name*/
                }
            } else {
                fprintf(stderr, "Invalid usage of output redirection\n");
                return;
            }
        }
    }

    execute_command(args);
}

char *get_full_path(char *command) {
    char *path_env = getenv("PATH");
    char *path = strtok(path_env, ":");
    char *full_path = malloc(MAX_PATH_LENGTH);

    while (path != NULL) {
        snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", path, command);
        if (access(full_path, X_OK) == 0) {
            return full_path;
        }
        path = strtok(NULL, ":");
    }

    free(full_path);
    return NULL;
}

void expand_variables(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (is_variable(args[i])) {
            substitute_variable(args[i]);
        }
    }
}

void get_variable_value(char *variable, char *value) {
    char *env_value = getenv(variable);
    if (env_value != NULL) {
        strcpy(value, env_value);
    } else {
        value[0] = '\0';
    }
}

bool is_variable(char *arg) {
    return arg[0] == '$';
}

void substitute_variable(char *arg) {
    char variable[MAX_COMMAND_LENGTH];
    char value[MAX_COMMAND_LENGTH];

    strcpy(variable, arg + 1);
    get_variable_value(variable, value);
    strcpy(arg, value);
}

int main(void) {
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];

    while (1) {
        display_prompt();
        read_command(command);
        parse_command(command, args);
        expand_variables(args);

        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                handle_exit();
            } else if (strcmp(args[0], "env") == 0) {
                handle_env();
            } else if (strcmp(args[0], "setenv") == 0) {
                handle_setenv(args);
            } else if (strcmp(args[0], "unsetenv") == 0) {
                handle_unsetenv(args);
            } else if (strcmp(args[0], "cd") == 0) {
                handle_cd(args);
            } else if (strcmp(args[0], "alias") == 0) {
                handle_alias(args);
            } else {
                char *full_path = get_full_path(args[0]);
                if (full_path != NULL) {
                    args[0] = full_path;
                    handle_redirection(args);
                } else {
                    printf("Command not found: %s\n", args[0]);
                }
            }
        }
    }

    return 0;
}
