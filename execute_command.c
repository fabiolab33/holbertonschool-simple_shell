#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

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
dprintf(STDERR_FILENO, "%s: %u: %s: not found\n",
name, line_number, args[0]);
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
dprintf(STDERR_FILENO, "%s: %u: %s: not found\n",
name, line_number, cmd_path);
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
