#include "shell.h"

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
        char *args[MAX_COMMAND_ARGS];
        args[0] = command->command;
        int i;
        for (i = 0; i < command->argCount; i++) {
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
    // Free command resources implementation
    // ...
}

void shell_loop() {
    char input[256];
    Command command;
    char *token;

    while (1) {
        printf("$ "); // or shell> if you prefer
        fgets(input, sizeof(input), stdin);

        // Tokenize the input
        token = strtok(input, " \n");
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
}
