#include "signals.h"

void handle_sigquit(int signum, siginfo_t *info, void *context)
{
	(void)context;
	
	if (signum == SIGQUIT)
		printf("SIGQUIT sent by %d\n", info->si_pid);
}

int trace_signal_sender(void)
{
	struct sigaction sa;

	sa.sa_sigaction = handle_sigquit;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);

	return (0);
}
