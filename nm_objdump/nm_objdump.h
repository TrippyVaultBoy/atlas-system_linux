#ifndef NM_OBJDUMP_H_
#define NM_OBJDUMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

void parse_elf_file(const char *filename);
void parse_symbol_table(void *elf, int is_64);

#endif