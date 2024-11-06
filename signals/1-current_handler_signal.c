#include "signals.h"

/**
* current_handler_signal - retrieves the current handler of the signal SIGINT
*
* Return: void
*/

void (*current_handler_signal(void))(int)
{
	void (*handler)(int) = signal(SIGINT, SIG_IGN);

	if (handler == SIG_IGN)
		return (NULL);

	signal(SIGINT, handler);

	return (handler);
}
