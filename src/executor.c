#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for fork, execvp
#include <sys/wait.h> // for wait
#include <string.h>
#include <fcntl.h> // open and file flags
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
        for (int i = 0; argv[i] != NULL; i++) {
            if (strcmp(argv[i], ">") == 0) {
                // Open or create file, create file if it dne, open file for writing only, truncate file, file mode (permissions)
                int fd = open(argv[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("Open failed");
                    exit(1);
                }
                // Redirect stdout to file
                dup2(fd, STDOUT_FILENO);
                close(fd);

                argv[i] = NULL;
                break;
            }
        }

        // execvp for the commands
        execvp(argv[0], argv); // replaces current process with new command
        perror("execvp failed\n");
        exit(1);
    } else {
        wait(NULL);
    }
}