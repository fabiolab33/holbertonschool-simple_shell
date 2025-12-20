#include "hsh.h"

/**
 * execute_command - executes a command
 * @args: arguments
 */
void execute_command(char **args)
{
pid_t pid;
int status;

pid = fork();
if (pid == 0)
{
if (execve(args[0], args, environ) == -1)
{
perror("./hsh");
exit(1);
}
}
else if (pid > 0)
wait(&status);
}
