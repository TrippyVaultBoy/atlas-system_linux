#include "readelf.h"

/**
* swap_uint32 - converts 32 bit
* Return: uint32_t
*/
uint32_t swap_uint32(uint32_t val)
{
	return ((val >> 24) & 0xff) |
			((val << 8) & 0xff0000) |
			((val >> 8) & 0xff00) |
			((val << 24) & 0xff000000);
}

/**
* swap_uint16 - converts 16 bit
* Return: uint16_t
*/
uint16_t swap_uint16(uint16_t val)
{
	return (val >> 8) | (val << 8);
}

/**
* print_header_32 - prints 32 bit elf files
* Return: void
*/
void print_header_32(Elf32_Ehdr *header)
{
	unsigned char *e_ident = header->e_ident;
	printf("ELF Header:\n"); 
	printf("  Magic:   ");
	for (int i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x ", e_ident[i]);
	}
	printf("\n");

	printf("  Class:                             ELF32\n");

	printf("  Data:                              ");
	unsigned char data = header->e_ident[EI_DATA];
	int is_big_endian = (data == ELFDATA2MSB);
	switch (data)
	{
		case ELFDATA2LSB: printf("2's complement, little endian\n"); break;
		case ELFDATA2MSB: printf("2's complement, big endian\n"); break;
		default: perror("Error: Cannot determine data encoding method");
	}

	printf("  Version:                           %d (current)\n", header->e_ident[EI_VERSION]);

	printf("  OS/ABI:                            ");
	switch (header->e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
		case ELFOSABI_LINUX: printf("UNIX - Linux\n"); break;
		case ELFOSABI_SOLARIS: printf("UNIX - Solaris\n"); break;
		case ELFOSABI_NETBSD: printf("UNIX - NetBSD\n"); break;
		default: printf("<unknown: %x>\n", header->e_ident[EI_OSABI]); break;
	}

	printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);

	printf("  Type:                              ");
	uint16_t e_type = is_big_endian ? swap_uint16(header->e_type) : header->e_type;
	switch (e_type)
	{
		case ET_NONE: printf("No file type\n"); break;
		case ET_REL: printf("REL (Relocatable file)\n"); break;
		case ET_EXEC: printf("EXEC (Executable file)\n"); break;
		case ET_DYN: printf("DYN (Shared object file)\n"); break;
		case ET_CORE: printf("CORE (Core file)\n"); break;
		default: printf("<unknown: %d>\n", header->e_type); break;
	}

	printf("  Machine:                           ");
	uint16_t e_machine = is_big_endian ? swap_uint16(header->e_machine) : header->e_machine;
	switch (e_machine)
	{
		case EM_NONE: printf("No machine\n"); break;
		case EM_386: printf("Intel 80386\n"); break;
		case EM_X86_64: printf("Advanced Micro Devices X86-64\n"); break;
		case EM_SPARC: printf("Sparc\n"); break;
		case EM_SPARC32PLUS: printf("Sun SPARC 32+\n"); break;
		case EM_SPARCV9: printf("SPARC V9\n"); break;
		case EM_AMDGPU: printf("AMD 64\n"); break;
		default: printf("<unknown: %d>\n", header->e_machine); break;
	}

	printf("  Version:                           0x%x\n", is_big_endian ? swap_uint32(header->e_version) : header->e_version);
	printf("  Entry point address:               0x%x\n", is_big_endian ? swap_uint32(header->e_entry) : header->e_entry);
	printf("  Start of program headers:          %d (bytes into file)\n", is_big_endian ? swap_uint32(header->e_phoff) : header->e_phoff);
	printf("  Start of section headers:          %d (bytes into file)\n", is_big_endian ? swap_uint32(header->e_shoff) : header->e_shoff);
	printf("  Flags:                             0x%x\n", is_big_endian ? swap_uint32(header->e_flags) : header->e_flags);
	printf("  Size of this header:               %d (bytes)\n", is_big_endian ? swap_uint16(header->e_ehsize) : header->e_ehsize);
	printf("  Size of program headers:           %d (bytes)\n", is_big_endian ? swap_uint16(header->e_phentsize) : header->e_phentsize);
	printf("  Number of program headers:         %d\n", is_big_endian ? swap_uint16(header->e_phnum) : header->e_phnum);
	printf("  Size of section headers:           %d (bytes)\n", is_big_endian ? swap_uint16(header->e_shentsize) : header->e_shentsize);
	printf("  Number of section headers:         %d\n", is_big_endian ? swap_uint16(header->e_shnum) : header->e_shnum);
	printf("  Section header string table index: %d\n", is_big_endian ? swap_uint16(header->e_shstrndx) : header->e_shstrndx);
}
