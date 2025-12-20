#include "shell.h"

/**
 * main - entry point
 *
 * Return - Always 0
 */
int main (void)
{
char *line = NULL;
size_t len = 0;
ssize_t read;

while (1)
{
prompt();

read = getline(&line, &len, stdin);
if (read == -1)
{
free(line);
exit(0);
}
line[read - 1] = '\0';

execute(line);
}
}
