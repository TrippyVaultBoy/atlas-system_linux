#ifndef GETLINE_H
#define GETLINE_H

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_SIZE 1024

char *_getline(const int fd);

#endif