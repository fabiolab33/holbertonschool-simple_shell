#include "shell.h"

#define PROMPT "#cisfun$ "

/**
 * shell_loop - main loop of the shell
 * @name: argv[0] for error formatting (if needed)
 *
 * Return: last command status
 */
int shell_loop(char *name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive = isatty(STDIN_FILENO);
	unsigned int line_number = 0;
	int last_status = 0;

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);

		nread = getline(&line, &len, stdin);

		/* ✅ Ctrl + D (EOF) */
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line_number++;

		/* remove newline */
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* skip leading spaces/tabs */
		{
			char *cmd = line;

			while (*cmd == ' ' || *cmd == '\t')
				cmd++;

			/* empty line */
			if (*cmd == '\0')
				continue;

			/* stop at first whitespace to enforce "one word" */
			{
				char *p = cmd;

				while (*p && *p != ' ' && *p != '\t')
					p++;
				*p = '\0';
			}

			/* build args for execve */
			{
				char *args[2];

				args[0] = cmd;
				args[1] = NULL;

				last_status = execute_command(args, name, line_number);
			}
		}
	}

	free(line);
	return (last_status);
}
