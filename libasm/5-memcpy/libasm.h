#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>

extern size_t asm_strlen(const char *str);
extern int asm_strcmp(const char *s1, const char *s2);
extern int asm_strncmp(const char *s1, const char *s2, size_t n);
extern char *asm_strchr(const char *s, int c);
extern char *asm_strstr(const char *haystack, const char *needle);
void *asm_memcpy(void *dest, const void *src, size_t n);

#endif
