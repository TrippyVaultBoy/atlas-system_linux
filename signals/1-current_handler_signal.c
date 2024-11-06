#include "signals.h"

void (*current_handler_signal(void))(int)
{
	void (*handler)(int) = signal(SIGINT, SIG_IGN);

	if (handler == SIG_IGN)
		return NULL;

	signal(SIGINT, handler);

	return handler;
}
