#ifndef SIGNALS_H_
#define SIGNALS_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int handle_signal(void);
void print_hello(int);
void set_print_hello(void);
void (*current_handler_signal(void))(int);

#endif