#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for fork, execvp
#include <sys/wait.h> // for wait
#include <string.h>
#include "../include/executor.h"
#include "../include/builtins.h"

void execute (char **argv) {
    // No command
    if (argv[0] == NULL) {
        return;
    }

    if (handle_builtin(argv)) {
        return; // built-in handled
    }

    // Handle built-in exit
    if (strcmp(argv[0], "exit") == 0) {
        exit(0);
    }

    pid_t pid = fork(); // Creates a new process
    if (pid < 0) {
        perror("Fork Fail\n");
        exit(1);
    } else if (pid == 0) {
        // execvp for the commands
        execvp(argv[0], argv); // replaces current process with new command
        perror("execvp failed\n");
        exit(1);
    } else {
        wait(NULL);
    }
}