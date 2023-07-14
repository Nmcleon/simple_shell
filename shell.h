#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 100

typedef struct {
    char command[MAX_COMMAND_LENGTH];
    char arguments[MAX_ARGUMENTS][MAX_COMMAND_LENGTH];
    int num_arguments;
} Command;

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
    if (strcmp(command->command, "exit") == 0) {
        exit(0);
    } else if (strcmp(command->command, "cd") == 0) {
        if (command->num_arguments == 2) {
            if (chdir(command->arguments[1]) != 0) {
                printf("Directory not found: %s\n", command->arguments[1]);
            }
        } else {
            printf("Invalid number of arguments for 'cd' command\n");
        }
    } else {
        printf("Unknown command: %s\n", command->command);
    }
}

void executeExternalCommand(Command *command) {
    pid_t pid = fork();

    if (pid == 0) {
        execvp(command->command, command->arguments);
        printf("Command not found: %s\n", command->command);
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        printf("Failed to fork process\n");
    }
}

void freeCommand(Command *command) {
    // No need to free dynamically allocated memory in this case
    // as all memory is allocated on the stack
    (void)command;  // Silence unused parameter warning
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
