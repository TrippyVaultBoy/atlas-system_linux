#include "signals.h"

/**
 * main - Entry point
 * @argc: argc
 * @argv: argv
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	int signum;
	char *desc;

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	signum = atoi(argv[1]);
	desc = strsignal(signum);
	if (desc)
		printf("%s: %s\n", argv[1], desc);
	else
		printf("Unknown signal: %d\n", signum);
	return (desc ? EXIT_SUCCESS : EXIT_FAILURE);
}
