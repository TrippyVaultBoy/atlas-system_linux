#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>

extern size_t asm_strlen(const char *str);
extern int asm_strcmp(const char *s1, const char *s2);
extern int asm_strncmp(const char *s1, const char *s2, size_t n);
extern char *asm_strchr(const char *s, int c);
extern char *asm_strstr(const char *haystack, const char *needle);
extern void *asm_memcpy(void *dest, const void *src, size_t n);
extern void *asm_memcpy(void *dest, const void *src, size_t n);
extern size_t asm_putc(int c);
extern size_t asm_puts(const char *str);
extern int asm_strcasecmp(const char *s1, const char *s2);

#endif
