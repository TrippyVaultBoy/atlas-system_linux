#include "signals.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	pid_t pid = (pid_t)atoi(argv[1]);

	if (kill(pid, SIGINT) == -1)
	{
		perror("Error sending signal");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}