#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

int _strlen(char *s);
int _atoi(char *s);
char **spt_args(char *buffer, char *del);

void handle_exit(char *first_arg, char *buffer, char **argv);
char *_getdir_forcamd(char *comd);
char *_getenv(const char *name);

#endif
