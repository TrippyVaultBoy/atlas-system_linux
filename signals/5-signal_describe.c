#include "signals.h"

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
		printf("%s\n", desc);
	else
		printf("Unknown signal: %d\n", signum);
	return (desc ? EXIT_SUCCESS : EXIT_FAILURE);
}
