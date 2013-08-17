#ifndef EVAL_H
#define EVAL_H


void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

#endif
