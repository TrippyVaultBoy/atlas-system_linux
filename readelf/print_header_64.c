#include "readelf.h"

/**
* print_header_64 - prints 64 bit elf files
* Return: void
*/
void print_header_64(Elf64_Ehdr *header) {
    unsigned char *e_ident = header->e_ident;
    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", e_ident[i]);
    }
    printf("\n");

    printf("  Class:                             ELF64\n");

    printf("  Data:                              ");
    unsigned char data = header->e_ident[EI_DATA];

    switch (data) {
        case ELFDATA2LSB: printf("2's complement, little endian\n"); break;
        case ELFDATA2MSB: printf("2's complement, big endian\n"); break;
        default: perror("Error: Cannot determine data encoding method");
    }

    printf("  Version:                           %d (current)\n", header->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            ");
    switch (header->e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
        case ELFOSABI_LINUX: printf("UNIX - Linux\n"); break;
        case ELFOSABI_SOLARIS: printf("UNIX - Solaris\n"); break;
        default: printf("<unknown: %x>\n", header->e_ident[EI_OSABI]); break;
    } 
    printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);
    printf("  Type:                              ");
    switch (header->e_type) {
        case ET_NONE: printf("No file type\n"); break;
        case ET_REL: printf("REL (Relocatable file)\n"); break;
        case ET_EXEC: printf("EXEC (Executable file)\n"); break;
        case ET_DYN: printf("DYN (Shared object file)\n"); break;
        case ET_CORE: printf("CORE (Core file)\n"); break;
        default: printf("<unknown: %d>\n", header->e_type); break;
    }
    printf("  Machine:                           ");
    switch (header->e_machine) {
        case EM_NONE: printf("No machine\n"); break;
        case EM_386: printf("Intel 80386\n"); break;
        case EM_X86_64: printf("Advanced Micro Devices X86-64\n"); break;
        case EM_SPARC: printf("Sparc\n"); break;
        case EM_SPARC32PLUS: printf("Sun SPARC 32+\n"); break;
        case EM_SPARCV9: printf("SPARC V9\n"); break;
        case EM_AMDGPU: printf("AMD 64\n"); break;
        default: printf("<unknown: %d>\n", header->e_machine); break;
    }
    printf("  Version:                           0x%x\n", header->e_version);
    printf("  Entry point address:               0x%lx\n", header->e_entry);
    printf("  Start of program headers:          %ld (bytes into file)\n", header->e_phoff);
    printf("  Start of section headers:          %ld (bytes into file)\n", header->e_shoff);
    printf("  Flags:                             0x%x\n", header->e_flags);
    printf("  Size of this header:               %d (bytes)\n", header->e_ehsize);
    printf("  Size of program headers:           %d (bytes)\n", header->e_phentsize);
    printf("  Number of program headers:         %d\n", header->e_phnum);
    printf("  Size of section headers:           %d (bytes)\n", header->e_shentsize);
    printf("  Number of section headers:         %d\n", header->e_shnum);
    printf("  Section header string table index: %d\n", header->e_shstrndx);
}