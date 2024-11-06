#include "signals.h"

void signal_handler(int signum)
{
    printf("Gotcha! [%d]\n", signum);
}

int handle_sigaction(void)
{
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1)
        return (-1);

    return (0);
}