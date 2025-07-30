#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/utils.h"

void trim_whitespace(char *str) {
    if (str == NULL) {
        return;
    }

    // Trim leading whitespacae
    char *start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    // Shift string if required
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
}

int is_whitespace_only(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return 0;
        }
        str++;
    }

    return 1;
}