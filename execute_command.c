#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
/**
 * print_error - print error message to stderr
 * @name: program name
 * @line_number: line number
 * @cmd: command that failed
 *
 * Return: void
 */
void print_error(char *name, unsigned int line_number, char *cmd)
{
char *msg1 = ": ";
char *msg2 = ": not found\n";
char num_str[20];
int i, len, temp;

write(STDERR_FILENO, name, strlen(name));
write(STDERR_FILENO, msg1, 2);
temp = line_number;
len = 0;
if (temp == 0)
len = 1;
else
{
while (temp > 0)
{
temp /= 10;
len++;
}
}
temp = line_number;
for (i = len - 1; i >= 0; i--)
{
num_str[i] = (temp % 10) + '0';
temp /= 10;
}
num_str[len] = '\0';
write(STDERR_FILENO, num_str, len);
write(STDERR_FILENO, msg1, 2);
write(STDERR_FILENO, cmd, strlen(cmd));
write(STDERR_FILENO, msg2, 12);
}

/**
 * _getenv - get environment variable value without using getenv
 * @name: variable name to find
 *
 * Return: pointer to value, or NULL if not found
 */
char *_getenv(char *name)
{
int i = 0;
size_t name_len;

if (!name || !environ)
return (NULL);
name_len = strlen(name);
while (environ[i])
{
if (strncmp(environ[i], name, name_len) == 0 &&
environ[i][name_len] == '=')
return (environ[i] + name_len + 1);
i++;
}
return (NULL);
}

/**
 * get_full_path - search PATH efor executable
 * @cmd: Command name
 *
 * Return: pointer to  full path (static buffer), or NULL if not found
 */
char *get_full_path(char *cmd)
{
static char full_path[PATH_MAX_LEN];
char *path_env, *dir, *path_copy;

if (!cmd)
return (NULL);
if (cmd[0] == '/' || cmd[0] == '.')
{
if (access(cmd, X_OK) == 0)
return (cmd);
return (NULL);
}
path_env = _getenv("PATH");
if (!path_env)
return (NULL);
path_copy = strdup(path_env);
if (!path_copy)
return (NULL);
dir = strtok(path_copy, ":");
while (dir)
{
snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
if (access(full_path, X_OK) == 0)
{
free(path_copy);
return (full_path);
}
dir = strtok(NULL, ":");
}
free(path_copy);
return (NULL);
}

/**
 * execute_command - Execute a command with arguments using PATH
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
char *cmd_path;

if (!args || !args[0])
return 0;

cmd_path = get_full_path(args[0]);
if (!cmd_path)
{
print_error(name, line_number, args[0]);
return (127);
}

pid = fork();
if (pid == -1)
{
perror("fork");
return (1);
}
else if (pid == 0) /* child */
{
if (execve(cmd_path, args, environ) == -1)
{
print_error(name, line_number, cmd_path);
_exit(127);
}
}
else /* parent */
{
if (waitpid(pid, &status, 0) == -1)
{
perror("waitpid");
return (1);
}

if (WIFEXITED(status))
return WEXITSTATUS(status);
else
return (1);
}

return (0);
}
