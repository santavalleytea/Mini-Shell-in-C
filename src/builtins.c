#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/builtins.h"
#include "../include/history.h"

int handle_builtin(char **argv) {
    if (argv[0] == NULL) {
        return 0;
    }

    char buffer[1024];

    if (strcmp(argv[0], "cd") == 0) {
        if (argv[1] == NULL) {
            chdir(getenv("HOME")); // changes current working directory
        } else {
            chdir(argv[1]);
        }
    } else if (strcmp(argv[0], "pwd") == 0) {
        // get cwd as string
        if (getcwd(buffer, sizeof(buffer)) != NULL) {
            printf("%s\n", buffer); 
        } else {
            perror("pwd");
        }

        return 1;

    } else if (strcmp(argv[0], "history") == 0) {
        print_history();
        return 1;
    }

    return 0;
}