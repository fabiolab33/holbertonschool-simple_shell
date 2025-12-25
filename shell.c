#include "shell.h"

/**
 * shell_loop - main shell loop
 * @name: program name
 */
void shell_loop(char *name)
{
char *line = NULL;
size_t len = 0;
ssize_t read;
pid_t pid;
int status;
int interactive;

interactive = isatty(STDIN_FILENO);

while (1)
{
if (interactive)
write(STDOUT_FILENO, "#cisfun$ ", 9);

read = getline(&line, &len, stdin);
if (read == -1)
break;

line[read - 1] = '\0';

pid = fork();
if (pid == 0)
{
char *args[2];

args[0] = line;
args[1] = NULL;

execve(line, args, environ);
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
