#ifndef HISTORY_H
#define HISTORY_H

void init_history(); // initialize data structure
void add_to_history(const char *line); // called for each command typed
void print_history(); // call when user types history
void free_history(); // called at shell exit to clean up

#endif