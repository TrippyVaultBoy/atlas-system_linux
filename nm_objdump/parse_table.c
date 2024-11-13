#include "nm_objdump.h"

void parse_symbol_table(void *elf, int is_64) {
    // Cast `elf` to `char *` to enable pointer arithmetic
    char *elf_bytes = (char *)elf;

    // First, get the ELF header and section header offset
    Elf64_Ehdr *ehdr64 = (Elf64_Ehdr *)elf;
    Elf32_Ehdr *ehdr32 = (Elf32_Ehdr *)elf;

    // Determine the section header offset and number of sections
    char *section_headers;
    int num_sections;
    if (is_64) {
        section_headers = elf_bytes + ehdr64->e_shoff;
        num_sections = ehdr64->e_shnum;
    } else {
        section_headers = elf_bytes + ehdr32->e_shoff;
        num_sections = ehdr32->e_shnum;
    }

    // Get the section header string table index
    int shstrndx = is_64 ? ehdr64->e_shstrndx : ehdr32->e_shstrndx;
    char *shstrtab = elf_bytes + (is_64 ? ((Elf64_Shdr *)section_headers)[shstrndx].sh_offset : ((Elf32_Shdr *)section_headers)[shstrndx].sh_offset);

    // Find the symbol table section and string table section
    char *symtab = NULL;
    char *strtab = NULL;
    size_t sym_entry_size = 0;
    size_t num_symbols = 0;

    for (int i = 0; i < num_sections; i++) {
        char *sh = section_headers + (is_64 ? sizeof(Elf64_Shdr) : sizeof(Elf32_Shdr)) * i;
        char *section_name = shstrtab + (is_64 ? ((Elf64_Shdr *)sh)->sh_name : ((Elf32_Shdr *)sh)->sh_name);

        // Check if this section is the symbol table
        if (strcmp(section_name, ".symtab") == 0) {
            symtab = elf_bytes + (is_64 ? ((Elf64_Shdr *)sh)->sh_offset : ((Elf32_Shdr *)sh)->sh_offset);
            sym_entry_size = is_64 ? sizeof(Elf64_Sym) : sizeof(Elf32_Sym);
            num_symbols = (is_64 ? ((Elf64_Shdr *)sh)->sh_size : ((Elf32_Shdr *)sh)->sh_size) / sym_entry_size;
        }
        // Check if this section is the string table
        else if (strcmp(section_name, ".strtab") == 0) {
            strtab = elf_bytes + (is_64 ? ((Elf64_Shdr *)sh)->sh_offset : ((Elf32_Shdr *)sh)->sh_offset);
        }
    }

    // Check if we found both the symbol table and string table
    if (!symtab || !strtab) {
        fprintf(stderr, "Error: Could not find symbol or string table\n");
        return;
    }

    // Process each symbol in the symbol table
    for (size_t i = 0; i < num_symbols; i++) {
        // Get symbol entry
        char *sym_entry = symtab + i * sym_entry_size;
        char *name = strtab + (is_64 ? ((Elf64_Sym *)sym_entry)->st_name : ((Elf32_Sym *)sym_entry)->st_name);
        unsigned char info = is_64 ? ((Elf64_Sym *)sym_entry)->st_info : ((Elf32_Sym *)sym_entry)->st_info;
        unsigned char bind = ELF64_ST_BIND(info);

        // Get the symbol value and section index
        size_t value = is_64 ? ((Elf64_Sym *)sym_entry)->st_value : ((Elf32_Sym *)sym_entry)->st_value;
        unsigned short section_index = is_64 ? ((Elf64_Sym *)sym_entry)->st_shndx : ((Elf32_Sym *)sym_entry)->st_shndx;

        // Determine symbol type character for `nm` output
        char sym_type = '?';
        if (section_index == SHN_UNDEF) {
            sym_type = 'U';  // Undefined
        } else if (section_index == SHN_ABS) {
            sym_type = 'A';  // Absolute
        } else if (bind == STB_LOCAL) {
            sym_type = 't';  // Local (usually lowercase)
        } else if (bind == STB_GLOBAL) {
            sym_type = 'T';  // Global
        }

        // Print symbol details in nm format
        printf("%016lx %c %s\n", value, sym_type, name);
    }
}