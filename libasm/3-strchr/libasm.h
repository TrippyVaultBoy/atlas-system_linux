#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>

extern size_t asm_strlen(const char *str);
extern int asm_strcmp(const char *s1, const char *s2);
extern int asm_strncmp(const char *s1, const char *s2, size_t n);
extern char *asm_strchr(const char *s, int c);

#endif
