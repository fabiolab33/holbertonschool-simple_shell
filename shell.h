#indef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

extern char **environ;

void prompt(void);
void execute(char *command);


#endif
