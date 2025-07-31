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

    int pipe_pos = -1;
    for (int i = 0; argv[i] != NULL; ++i) {
        if (strcmp(argv[i], "|") == 0){
            pipe_pos = i;
            break;
        }
    }

    if (pipe_pos != -1) {
        argv[pipe_pos] = NULL;
        char **left_argv = argv;
        char **right_argv = &argv[pipe_pos + 1];

        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("Pipe");
            exit(1);
        }

        pid_t pid1 = fork();
        if (pid1 == 0) {
            // Child 1; stdout to pipe
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            execvp(left_argv[0], left_argv);
            perror("execvp failed");
            exit(1);
        }

        pid_t pid2 = fork();
        if (pid2 == 0) {
            // Child 2; stdin to pipe
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[1]);
            close(pipefd[0]);
            execvp(right_argv[0], right_argv);
            perror("execvp failed");
            exit(1);
        }

        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        return;
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
            if (strcmp(argv[i], "<") == 0) {
                int fd = open(argv[i+1], O_RDONLY);
                if (fd < 0) {
                    perror("Open failed");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
                argv[i] = NULL;
                break;
            }

            if (strcmp(argv[i], ">>") == 0) {
                int fd = open(argv[i+1], O_WRONLY | O_CREAT |O_APPEND, 0644);
                if (fd < 0) {
                    perror("Open failed");
                    exit(1);
                }
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