#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/history.h"

#define MAX_HISTORY 100

static char *history[MAX_HISTORY];
static int history_count = 0;

// Initialize global history array
void init_history() {
    for (int i = 0; i < MAX_HISTORY; i++) {
        history[i] = NULL;
    }
}

// Add history to array
void add_to_history(const char *line) {
    if (history_count == MAX_HISTORY) {
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i-1] = history[i];
            history_count--;
        }
    }

    history[history_count++] = strdup(line);
}

// Print each history
void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i+1, history[i]);
    }
}

// Free each history elements in array
void free_history() {
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }
}