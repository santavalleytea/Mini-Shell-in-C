#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/parser.h"

#define MAX_TOKEN 64

char **parse_input(char *input) {
    char **argv = malloc(MAX_TOKEN * sizeof(char *));
    int i = 0;
    char *token = strtok(input, " ");

    while (token != NULL && i < MAX_TOKEN - 1) {
        argv[i] = strdup(token);
        i++;
        token = strtok(NULL, " ");
    }

    argv[i] = NULL;
    return argv;
}

void free_argv(char **argv) {
    for (int i = 0; argv[i] != NULL; ++i) {
        free(argv[i]); // free each string
    }
    free(argv);     // free the array itself
}