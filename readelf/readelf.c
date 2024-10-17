#include "readelf.h"

/**
* main - entry point
* Return: 1 or 0
*/
int main(int argc, char *argv[]) {
    int fd;
    Elf64_Ehdr elf_header;

    if (argc != 2) {
        perror("Error: exactly two arguments should be used");
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error: cannot open file");
        return 1;
    }

    if (read(fd, &elf_header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
        perror("Error reading ELF header");
        close(fd);
        return 1;
    }

    if (elf_header.e_ident[EI_CLASS] == ELFCLASS32) {
        Elf32_Ehdr elf32_header;
        lseek(fd, 0, SEEK_SET);
        read(fd, &elf32_header, sizeof(Elf32_Ehdr)); 
        print_header_32(&elf32_header);
    } else if (elf_header.e_ident[EI_CLASS] == ELFCLASS64) {
        print_header_64(&elf_header);
    }

    close(fd);
    return 0;
}