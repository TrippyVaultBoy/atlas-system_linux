#ifndef LAPS_H
#define LAPS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int find_car(int id);
void add_car(int id);
int compare_cars(const void *a, const void *b);
void race_state(int *id, size_t size);

#endif
