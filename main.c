#include "shell.h"

/**
 * print_prompt - prints prompt if interactive
 * @interactive: 1 if interactive, 0 otherwise
 */
static void print_prompt(int interactive)
{
	if (interactive)
		write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
}

/**
 * trim_newline - removes trailing newline from getline
 * @line: input line
 */
static void trim_newline(char *line)
{
	size_t i = 0;

	if (!line)
		return;

	while (line[i] != '\0')
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return;
		}
		i++;
	}
}

/**
 * trim_spaces - removes leading/trailing spaces and tabs
 * @s: string to trim (modified in place)
 * Return: pointer to trimmed string (inside same buffer)
 */
static char *trim_spaces(char *s)
{
	char *end;

	if (!s)
		return (s);

	/* Trim leading spaces/tabs */
	while (*s == ' ' || *s == '\t')
		s++;

	if (*s == '\0')
		return (s);

	/* Trim trailing spaces/tabs */
	end = s;
	while (*end)
		end++;
	end--;

	while (end > s && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}

	return (s);
}

/**
 * exec_one_word - executes a one-word command (no args)
 * @shell_name: argv[0] of the shell (used for perror prefix)
 * @cmd: command string (e.g., "/bin/ls")
 * Return: 0 if attempted execution, 1 if empty/not executable
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
		/* Checker expects perror-style output */
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
		/* If execve returns, it failed */
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

		print_prompt(interactive);

		nread = getline(&line, &cap, stdin);
		if (nread == -1)
		{
			/* Ctrl+D (EOF) */
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		trim_newline(line);
		cmd = trim_spaces(line);

		/* Ignore empty lines or lines that become empty after trimming */
		if (cmd[0] == '\0')
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
