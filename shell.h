#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

#define MAX_ARGS 128

/* Function prototypes */
int shell_loop(char *name);
int execute_command(char **args, char *name, unsigned int line_number);

#endif /* SHELL_H */
