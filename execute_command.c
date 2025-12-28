#include "shell.h"

/**
 * execute_command - Execute a command with arguments
 * @args: Array of command arguments (NULL-terminated)
 * @name: Program name (argv[0]) for error messages
 * @line_number: Current line number
 *
 * Return: Exit status of command
 */
int execute_command(char **args, char *name, unsigned int line_number)
{
pid_t pid;
int status;

if (args == NULL || args[0] == NULL)
return (0);

pid = fork();
if (pid == -1)
{
perror("fork");
return (1);
}
else if (pid == 0)
{
if (execve(args[0], args, environ) == -1)
{
fprintf(stderr, "%s: %u: %s: not found\n",
name, line_number, args[0]);
exit(127);
}
}
else
{
waitpid(pid, &status, 0);
if (WIFEXITED(status))
return (WEXITSTATUS(status));
}

return (0);
}
