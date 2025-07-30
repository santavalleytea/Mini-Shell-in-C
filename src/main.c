#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/history.h"
#include "../include/utils.h"

int main() {
    init_history();
    char *line = NULL; // buffer that getline will allocate
    size_t bufsize = 0; // size of buffer

    while (1) {
        printf("minishell>");
        fflush(stdout); // prompt shows before input
        ssize_t len = getline(&line, &bufsize, stdin);

        add_to_history(line);

        if (len == -1) {
            printf("\nExiting shell...\n");
            break;
        }
        // Remove new line
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Skip if whitespace or nothing
        if (strlen(line) == 0) {
            continue;
        }

        trim_whitespace(line);
        if (is_whitespace_only(line)) {
            continue;
        }
        
        char **argv = parse_input(line);

        execute(argv);

        free_argv(argv);

    }

    free(line);
    free_history();
    return 0;
}