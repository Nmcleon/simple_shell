#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_ARGS 1024

typedef struct {
    char command[256];
    char arguments[MAX_COMMAND_ARGS][256];
    int argCount;
} Command;

void executeBuiltInCommand(Command *command) {
    if (strcmp(command->command, "cd") == 0) {
        if (chdir(command->arguments[0]) != 0) {
            perror("cd");
        }
    }
    // Add other built-in commands here
}

void executeExternalCommand(Command *command) {
    pid_t pid = fork();
    if (pid == 0) {
        char *args[MAX_COMMAND_ARGS];
        args[0] = command->command;
        for (int i = 0; i < command->argCount; i++) {
            args[i + 1] = command->arguments[i];
        }
        args[command->argCount + 1] = NULL;

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
    // Add deallocation of dynamically allocated memory, if any
    (void)command; // Remove the unused parameter warning
}

int main() {
    char input[256];
    Command command;

    while (1) {
        printf("$ "); //change shell> with $ if $ is preferred
        fgets(input, sizeof(input), stdin);

        // Tokenize the input
        char *token = strtok(input, " \n");
        if (token == NULL) {
            continue; // Empty command, prompt again
        }

        // Extract the command
        strcpy(command.command, token);

        // Extract the arguments
        command.argCount = 0;
        while ((token = strtok(NULL, " \n")) != NULL) {
            strcpy(command.arguments[command.argCount], token);
            command.argCount++;
            if (command.argCount >= MAX_COMMAND_ARGS) {
                break;
            }
        }

        // Execute the command
        if (strcmp(command.command, "exit") == 0) {
            break; // Exit the shell
        } else if (strcmp(command.command, "cd") == 0) {
            executeBuiltInCommand(&command);
        } else {
            executeExternalCommand(&command);
        }
    }

    // Clean up and exit
    freeCommand(&command);
    return 0;
}
