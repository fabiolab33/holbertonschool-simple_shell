#include "shell.h"
#include <string.h>

extern char **environ;

/**
 * shell_loop - main shell loop
 * @name: program name
 */
void shell_loop(char *name)
{
char *line;
size_t len;
ssize_t read;
pid_t pid;
int status;
int interactive;
char *args[100];
int i;
char *token;

line = NULL;
len = 0;
interactive = isatty(STDIN_FILENO);

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
 while (token != NULL && i < 99)
   {
     args[i] = token;
     i++;
     token = strtok(NULL, " \t");
   }
 args[i] = NULL;

 if (args[0] == NULL)
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
