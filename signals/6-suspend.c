#include "signals.h"

void handle_sigint(int signum)
{
    printf("Caught %d\n", signum);
    printf("Signal received\n");
    _Exit(EXIT_SUCCESS);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    pause();

    return (EXIT_SUCCESS);
}
