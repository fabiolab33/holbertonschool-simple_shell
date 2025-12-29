#include "shell.h"
#define PROMPT "$ "

/**
 * build_args - split a line into tokens (argv) by spaces/tabs
 * @line: input line (will be modified)
 * @args: output argv array
 *
 * Return: number of args
 */
static int build_args(char *line, char **args)
{
int i = 0;
char *token;

token = strtok(line, " \t");
while (token != NULL && i < (MAX_ARGS - 1))
{
args[i++] = token;
token = strtok(NULL, " \t");
}
args[i] = NULL;
return (i);
}

/**
 * shell_loop - main shell loop
 * @name: argv[0] (shell name)
 *
 * Return: last command exit status
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
char *args[MAX_ARGS];
int argc;

if (interactive)
write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);

nread = getline(&line, &len, stdin);

/* EOF (Ctrl+D) */
if (nread == -1)
{
if (interactive)
write(STDOUT_FILENO, "\n", 1);
break;
}

line_number++;

/* strip newline */
if (nread > 0 && line[nread - 1] == '\n')
line[nread - 1] = '\0';

/* tokenize into argv */
argc = build_args(line, args);

/* empty / spaces-only line */
if (argc == 0)
continue;

last_status = execute_command(args, name, line_number);
}

free(line);
return (last_status);

}
