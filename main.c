#include "shell.h"

/**
 * main - Entry point for the shell
 * @argc: Argument count (not used)
 * @argv: Argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
(void)argc;
shell_loop(argv[0]);
return (0);
}
