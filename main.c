#include "shell.h"

/**
 * main - Entry point for simple shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Exit status from shell_loop
 */
int main(int argc, char *argv[])
{
	(void)argc;

	return (shell_loop(argv[0]));
}
