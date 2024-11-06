#include "signals.h"

void (*current_handler_sigaction(void))(int)
{
	struct sigaction sa;

	if (sigaction(SIGINT, NULL, &sa) == -1)
		return (NULL);

	return (sa.sa_handler);
}
