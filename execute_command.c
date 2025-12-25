#include "shell.h"

/**
 * execute_command - forks and executes a command (NO PATH searching)
 * @args: argv array (args[0] is command, args[1..] are arguments)
 * @shell_name: argv[0] for shell (unused here but kept for your prototype)
 * @line_number: line counter (unused here but kept for your prototype)
 *
 * Return: child exit status, or 1 on error
 */
int execute_command(char **args, char *shell_name, unsigned int line_number)
{
	pid_t pid;
	int status;

	(void)shell_name;
	(void)line_number;

	if (args == NULL || args[0] == NULL)
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

		/* ✅ error must blame the command that failed */
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
