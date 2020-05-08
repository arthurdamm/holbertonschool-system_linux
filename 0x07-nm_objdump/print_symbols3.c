#include "hreadelf.h"

/**
 * get_sym_type - gets the STT type
 * @elf_header: the internal header
 * @i: index of the current symbol struct
 * Return: string type
 */
char *get_sym_type(elf_t *elf_header, size_t i)
{
	switch (YGET(i, st_info) & 0xf)
	{
		case STT_NOTYPE: return ("NOTYPE");
		case STT_OBJECT: return ("OBJECT");
		case STT_FUNC: return ("FUNC");
		case STT_SECTION: return ("SECTION");
		case STT_FILE: return ("FILE");
		case STT_COMMON: return ("COMMON");
		case STT_TLS: return ("TLS");
		case STT_NUM: return ("NUM");
		case STT_LOOS: return ("LOOS");
		case STT_HIOS: return ("HIOS");
		case STT_LOPROC: return ("LOPROC");
		case STT_HIPROC: return ("HIPROC");
		default: return ("UNKNOWN");
	}
}

/**
 * get_sym_bind - gets the STB type
 * @elf_header: the internal header
 * @i: index of the current symbol struct
 * Return: string bind type
 */
char *get_sym_bind(elf_t *elf_header, size_t i)
{
	switch (YGET(i, st_info) >> 4)
	{
		case STB_LOCAL: return ("LOCAL");
		case STB_GLOBAL: return ("GLOBAL");
		case STB_WEAK: return ("WEAK");
		case STB_NUM: return ("NUM");
		case STB_LOOS: return ("LOOS");
		case STB_HIOS: return ("HIOS");
		case STB_LOPROC: return ("LOPROC");
		case STB_HIPROC: return ("HIPROC");
		default: return ("UNKNWN");
	}
}

/**
 * get_sym_visibility - gets the STV type
 * @elf_header: the internal header
 * @i: index of the current symbol struct
 * Return: string visibility type
 */
char *get_sym_visibility(elf_t *elf_header, size_t i)
{
	switch (YGET(i, st_other) & 0x3)
	{
		case STV_DEFAULT: return ("DEFAULT");
		case STV_INTERNAL: return ("INTERNAL");
		case STV_HIDDEN: return ("HIDDEN");
		case STV_PROTECTED: return ("PROTECTED");
		default: return ("UNKNOWN");
	}
}

/**
 * get_nm_type64 - gets type of symbol in one char
 * @sym: the symbol struct
 * @shdr: the array of section header structs
 * Return: the char type
 */
char get_nm_type64(Elf64_Sym sym, Elf64_Shdr *shdr)
{
	char c;

	if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
		ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
		c = sym.st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
		c = sym.st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (sym.st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym.st_shndx == SHN_ABS)
		c = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		c = 'C';
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
		c = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}

/**
 * get_nm_type32 - gets type of symbol in one char
 * @sym: the symbol struct
 * @shdr: the array of section header structs
 * Return: the char type
 */
char get_nm_type32(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char  c;

	if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK &&
		ELF32_ST_TYPE(sym.st_info) == STT_OBJECT)
		c = sym.st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK)
		c = sym.st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (sym.st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym.st_shndx == SHN_ABS)
		c = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		c = 'C';
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
		c = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
			&& shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	if (ELF32_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}
