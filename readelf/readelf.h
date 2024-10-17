#ifndef READELF_H_
#define READELF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

void print_header_32(Elf32_Ehdr *header);
void print_header_64(Elf64_Ehdr *header);
uint32_t swap_uint32(uint32_t val);
uint16_t swap_uint16(uint16_t val);

#endif