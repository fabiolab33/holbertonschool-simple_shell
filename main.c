#include "shell.h"

/**
 * exec_one_word - executes a command (no args, no PATH)
 * @shell_name: argv[0] used for perror prefix
 * @cmd: command string (must be direct path like /bin/ls)
 * Return: 0 if attempted execution, 1 otherwise
 */
static int exec_one_word(const char *shell_name, char *cmd)
{
	pid_t pid;
	int status;
	char *argv[2];

	if (!cmd || cmd[0] == '\0')
		return (1);

	/* Task 2: no PATH. Only direct executable paths should work. */
	if (access(cmd, X_OK) != 0)
	{
		perror(shell_name);
		return (1);
	}

	argv[0] = cmd;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror(shell_name);
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd, argv, environ);
		perror(shell_name);
		_exit(127);
	}

	(void)waitpid(pid, &status, 0);
	return (0);
}

/**
 * run_shell - main shell loop
 * @shell_name: argv[0]
 * Return: 0
 */
int run_shell(const char *shell_name)
{
	char *line = NULL;
	size_t cap = 0;
	ssize_t nread;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		char *cmd;

		if (interactive)
			write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);

		nread = getline(&line, &cap, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* ✅ whitespace-safe: gets first word token */
		cmd = strtok(line, " \t\r\n\v\f");
		if (!cmd)
			continue;

		exec_one_word(shell_name, cmd);
	}

	free(line);
	return (0);
}

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0
 */
int main(int ac, char **av)
{
	(void)ac;
	return (run_shell(av[0]));
}
