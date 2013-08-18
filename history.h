#ifndef HISTORY_H
#define HISTORY_H

#define HISTORY_MAX_SIZE 20

void add_command_to_history(char *cmd);
char *get_prev_cmd(int n);
int is_prev_command(char *cmd);
void print_history();
#endif