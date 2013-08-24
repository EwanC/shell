#ifndef COMPLETER_H
#define COMPLETER_H

#define MAX_PATHS 20

void init_readline();
char *dupstr (char *s);
void get_command_list();
char **split_path();

#endif