#include "signals.h"
/**
* current_handler_sigaction - retrieves the current 
* handler of the signal SIGINT
*
* Return: NULL or pointer
*/

void (*current_handler_sigaction(void))(int)
{
	struct sigaction sa;

	if (sigaction(SIGINT, NULL, &sa) == -1)
		return (NULL);

	return (sa.sa_handler);
}
