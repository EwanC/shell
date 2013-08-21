#ifndef BUILTIN_H
#define BUILTIN_H

int builtin_command(char **argv);
int prev_cmd(char **argv);
int stdin_redirect(char **argv);
int stdout_redirect(char **argv);
void change_dir(char **argv);
void print_help();

#endif