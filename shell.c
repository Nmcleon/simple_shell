#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "shell.h"

void readCommand(Command *command) {
    char input[MAX_COMMAND_LENGTH];
    char *token; /*Declare token before any other statements*/
    printf("Enter a command: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  /* Remove trailing newline character */

    token = strtok(input, " ");
    command->num_arguments = 0;

    while (token != NULL && command->num_arguments < MAX_ARGUMENTS) {
        strcpy(command->arguments[command->num_arguments], token);
        command->num_arguments++;
        token = strtok(NULL, " ");
    }
    strcpy(command->command, command->arguments[0]);
}

void executeBuiltInCommand(Command *command) {
    if (strcmp(command->command, "cd") == 0) {
        /* Change directory implementation */
    }
    /* Add other built-in commands here */
}

void executeExternalCommand(Command *command) {
    pid_t pid = fork();
    int i; /* Declare i before the for loop*/
    if (pid == 0) {
        char *args[MAX_ARGUMENTS + 2];
        args[0] = command->command;
        for (i = 0; i < command->num_arguments; i++) {
            args[i + 1] = command->arguments[i];
        }
        args[command->num_arguments + 1] = NULL;

        execvp(command->command, args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}


void freeCommand(Command *command) {
    /* Free command resources implementation */
    
    (void)command; /* Silence unused parameter warning */
}

int main() {
    Command command;

    while (1) {
        readCommand(&command);

        if (strcmp(command.command, "") == 0) {
            continue;
        }

        if (strcmp(command.command, "help") == 0) {
            printf("This is a simple shell program.\n");
            printf("Supported commands:\n");
            printf("- exit: Exit the shell\n");
            printf("- cd [directory]: Change the current directory\n");
            printf("- help: Display this help message\n");
        } else if (strcmp(command.command, "cd") == 0 || strcmp(command.command, "exit") == 0) {
            executeBuiltInCommand(&command);
        } else {
            executeExternalCommand(&command);
        }
    }

    freeCommand(&command);

    return 0;
}
