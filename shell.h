#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* main shell loop */
int shell_loop(char *name);

/* command execution */
int execute_command(char **args, char *shell_name, unsigned int line_number);

#endif /* SHELL_H */
