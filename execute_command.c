#include "shell.h"

/**
 * execute_command - Forks and executes a command (no PATH, no args)
 * @args: token array (args[0] is the command, args[1] must be NULL)
 * @shell_name: argv[0] (not required for perror)
 * @line_number: command counter (optional for formatted errors)
 *
 * Return: exit status of child, or 1 on failure
 */
int execute_command(char **args, char *shell_name, unsigned int line_number)
{
	pid_t pid;
	int status;

	(void)shell_name;
	(void)line_number;

	if (!args || !args[0])
		return (0);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		execve(args[0], args, environ);

		/* ✅ Print error for the COMMAND, not "./hsh" */
		perror(args[0]);
		exit(127);
	}

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
