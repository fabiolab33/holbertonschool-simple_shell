#include "shell.h"

/**
 * main - Entry point for the shell
 * @argc: Argument count (unused)
 * @argv: Argument vector
 *
 * Return: exit status of the shell
 */
int main(int argc, char **argv)
{
	int status;

	(void)argc;

	status = shell_loop(argv[0]);
	return (status);
}
