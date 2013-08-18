//Defines commonly used functions and libraries

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define MAXARGS 128
#define MAXLINE 8192

extern char **environ; //Environmental variables

void unix_error(char *msg);
pid_t Fork(void);
char *get_path(char *path, size_t size);
void sig_handler(int sig);
void int_handler(int sig);


#endif