#include "shell.h"

/**
 * get_full_path - search PATH for executable
 * @cmd: command name
 *
 * Return: pointer to full path (static buffer), or NULL if not found
 */
char *get_full_path(char *cmd)
{
    static char full_path[PATH_MAX_LEN];
    char *path_env, *dir, *path_copy;

    if (cmd == NULL)
        return (NULL);

    if (cmd[0] == '/' || cmd[0] == '.')
    {
        if (access(cmd, X_OK) == 0)
            return cmd;
        else
            return NULL;
    }

    path_env = getenv("PATH");
    if (!path_env)
        return NULL;

    path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
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
