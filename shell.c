#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "shell.h"

void readCommand(Command *command) {
    printf("Enter a command: ");
    fgets(command->command, sizeof(command->command), stdin);
    command->command[strcspn(command->command, "\n")] = '\0';  // Remove trailing newline character

    char *token = strtok(command->command, " ");
    command->num_arguments = 0;

    while (token != NULL && command->num_arguments < MAX_ARGUMENTS) {
        strcpy(command->arguments[command->num_arguments++], token);
        token = strtok(NULL, " ");
    }
}

void executeBuiltInCommand(Command *command) {
    if (strcmp(command->command, "cd") == 0) {
        // Change directory implementation
        // ...
    }
    /* Add other built-in commands here */
}

void executeExternalCommand(Command *command) {
    pid_t pid = fork();
    if (pid == 0) {
        char *args[MAX_ARGUMENTS + 2];
        args[0] = command->command;
        for (int i = 0; i < command->num_arguments; i++) {
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
    // Free command resources implementation
    // ...
    (void)command; // Silence unused parameter warning
}

void shell_loop() {
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
}
