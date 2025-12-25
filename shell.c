#include "shell.h"
#include <string.h>

extern char **environ;

/**
 * shell_loop - Main loop of the shell
 * @name: Program name
 */
void shell_loop(char *name)
{
char *line = NULL;
size_t len = 0;
ssize_t read;
pid_t pid;
int status;
int interactive = isatty(STDIN_FILENO);
char *args[100];
int i;
char *token;

while (1)
{
if (interactive)
write(STDOUT_FILENO, "#cisfun$ ", 9);

read = getline(&line, &len, stdin);
if (read == -1)
break;

if (read > 0 && line[read - 1] == '\n')
line[read - 1] = '\0';

i = 0;
token = strtok(line, " \t");
while (token && i < 99)
{
args[i++] = token;
token = strtok(NULL, " \t");
}
args[i] = NULL;

if (!args[0])
continue;

pid = fork();
if (pid == 0)
{
execve(args[0], args, environ);
perror(name);
exit(EXIT_FAILURE);
}
else if (pid > 0)
{
wait(&status);
}
}
free(line);
}
