#include "headers.h"

void execute_foreground(char *command) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        char *args[] = {command, NULL};
        execvp(command, args);
        perror("Error executing command");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        waitpid(pid, &status, 0);
    } else {
        perror("Error forking");
    }
}