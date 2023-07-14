#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 100

typedef struct {
    char command[MAX_COMMAND_LENGTH];
    char arguments[MAX_ARGUMENTS][MAX_COMMAND_LENGTH];
    int num_arguments;
} Command;

void readCommand(Command *command);
void executeBuiltInCommand(Command *command);
void executeExternalCommand(Command *command);
void freeCommand(Command *command);
void shell_loop();

#endif
