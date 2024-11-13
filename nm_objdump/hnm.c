#include "nm_objdump.h"

int main(int argc, char **argv) {
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s [objfile ...]\n", argv[0]);
		exit(1);
	}

	for (int i = 1; i < argc; i++)
	{
		parse_elf_file(argv[i]);
	}
	return (0);
}

void parse_elf_file(const char *filename) {
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return;
	}

	struct stat st;
	
	if (fstat(fd, &st) < 0)
	{
		perror("fstat error");
		close(fd);
		return;
	}

	void *elf = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (elf == MAP_FAILED)
	{
		perror("mmap error");
		close(fd);
		return;
	}

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)elf;
	int is_64 = ehdr->e_ident[EI_CLASS] == ELFCLASS64;

	parse_symbol_table(elf, is_64);

	munmap(elf, st.st_size);
	close(fd);
}