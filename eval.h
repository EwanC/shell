#ifndef EVAL_H
#define EVAL_H


void eval(char *cmdline);
int parseline(char *buf, char **argv);
void execute_cmd(char **argv, int bg);
#endif
