#ifndef HSH_H
#define HSH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

void shell_loop(void);
char **parse_line(char *line);
void execute_command(char **args);

#endif
