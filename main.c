#include "shell.h"

/**
<<<<<<< HEAD
 * exec_one_word - executes a command (no args, no PATH)
 * @shell_name: argv[0] used for perror prefix
 * @cmd: command string (must be direct path like /bin/ls)
 * Return: 0 if attempted execution, 1 otherwise
=======
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
 * exec_one_word - executes a command line that is only one word (no args)
 * @shell_name: argv[0] of the shell (used for errors)
 * @cmd: command string (like "/bin/ls")
 * Return: 0 on success path, 1 if cmd empty or not executable
>>>>>>> origin/main
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
<<<<<<< HEAD
=======
		/* Matches the sample style: "./shell: No such file or directory" */
>>>>>>> origin/main
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
<<<<<<< HEAD
=======
		/* If execve returns, it failed */
>>>>>>> origin/main
		perror(shell_name);
		_exit(127);
	}

	(void)waitpid(pid, &status, 0);
	return (0);
}

/**
<<<<<<< HEAD
 * run_shell - main loop
 * @shell_name: argv[0]
 * Return: 0
=======
 * run_shell - main shell loop
 * @shell_name: argv[0]
 * Return: 0 always
>>>>>>> origin/main
 */
int run_shell(const char *shell_name)
{
	char *line = NULL;
	size_t cap = 0;
	ssize_t nread;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
<<<<<<< HEAD
		char *cmd;

		if (interactive)
			write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
=======
		print_prompt(interactive);
>>>>>>> origin/main

		nread = getline(&line, &cap, stdin);
		if (nread == -1)
		{
<<<<<<< HEAD
=======
			/* Ctrl+D (EOF) */
>>>>>>> origin/main
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

<<<<<<< HEAD
		/* ✅ Tokenize by ANY whitespace: fixes leading/trailing spaces */
		cmd = strtok(line, " \t\r\n\v\f");
		if (!cmd)
			continue;

		exec_one_word(shell_name, cmd);
=======
		trim_newline(line);

		/* One word only, no args parsing */
		exec_one_word(shell_name, line);
>>>>>>> origin/main
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
