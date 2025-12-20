#include "shell.h"

/**
 * trim_line - Remove leading and trailing whitespace
 * @str: String to trim
 * Return: Pointer to trimmed string
 */
char *trim_line(char *str)
{
	char *end;

	/* Trim leading space */
	while (isspace((unsigned char)*str))
		str++;

	if (*str == 0)  /* All spaces? */
		return (str);

	/* Trim trailing space */
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;

	/* Write new null terminator */
	end[1] = '\0';

	return (str);
}

/**
 * main - Simple shell main loop
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL, *trimmed;
	size_t len = 0;
	ssize_t read;
	char *args[2];
	int status;
	pid_t pid;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		trimmed = trim_line(line);

		if (trimmed[0] == '\0')
			continue;

		if (strcmp(trimmed, "exit") == 0)
			break;

		args[0] = trimmed;
		args[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror(argv[0]);
			continue;
		}

		if (pid == 0)
		{
			if (execve(args[0], args, env) == -1)
			{
				fprintf(stderr, "%s: No such file or directory\n", argv[0]);
				exit(127);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}

	free(line);
	return (0);
}
