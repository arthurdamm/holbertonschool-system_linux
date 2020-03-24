#include "hreadelf.h"

/**
 * print_machine - prints the target machine type
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_machine(Elf64_Ehdr *elf_header)
{
	printf("  Machine:                           ");
	if (get_machine(elf_header))
		printf("%s", get_machine(elf_header));
	else
		printf("<unknown>: 0x%x", elf_header->e_machine);
	printf("\n");
	return (0);
}

/**
 * print_e_version - prints the e_version value
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_e_version(elf_t *elf_header)
{
	printf("  Version:                           0x%lx\n",
		IS_32(elf_header->e64)
			? (unsigned long)elf_header->e32.e_version
			: (unsigned long)elf_header->e64.e_version);
	return (0);
}

/**
 * print_program_headers - prints the start of program headers
 * @elf_header: address of elf header struct
 * Return: 0 on success else exit_status
 */
int print_program_headers(elf_t *elf_header)
{
	printf("  Start of program headers:          %lu (bytes into file)\n",
		EGET(e_phoff));
	return (0);
}

/**
 * get_machine - gets the target machine type string
 * @elf_header: address of elf header struct
 * Return: the string or NULL
 */
char *get_machine(Elf64_Ehdr *elf_header)
{
	switch (elf_header->e_machine)
	{
	case EM_NONE: return ("None");
	case EM_AARCH64: return ("AArch64");
	case EM_M32: return ("WE32100");
	case EM_SPARC: return ("Sparc");
	case EM_386: return ("Intel 80386");
	case EM_68K: return ("MC68000");
	case EM_88K: return ("MC88000");
	case EM_860: return ("Intel 80860");
	case EM_MIPS: return ("MIPS R3000");
	case EM_S370: return ("IBM System/370");
	case EM_MIPS_RS3_LE: return ("MIPS R4000 big-endian");
	case EM_PARISC: return ("HPPA");
	case EM_SPARC32PLUS: return ("Sparc v8+");
	case EM_960: return ("Intel 90860");
	case EM_PPC: return ("PowerPC");
	case EM_PPC64: return ("PowerPC64");
	case EM_FR20: return ("Fujitsu FR20");
	case EM_RH32: return ("TRW RH32");
	case EM_ARM: return ("ARM");
	case EM_SH: return ("Renesas / SuperH SH");
	case EM_SPARCV9: return ("Sparc v9");
	case EM_TRICORE: return ("Siemens Tricore");
	case EM_ARC: return ("ARC");
	case EM_H8_300: return ("Renesas H8/300");
	case EM_H8_300H: return ("Renesas H8/300H");
	case EM_H8S: return ("Renesas H8S");
	case EM_H8_500: return ("Renesas H8/500");
	case EM_IA_64: return ("Intel IA-64");
	case EM_MIPS_X: return ("Stanford MIPS-X");
	case EM_COLDFIRE: return ("Motorola Coldfire");
	case EM_ALPHA: return ("Alpha");
	case EM_D10V: return ("d10v");
	case EM_D30V: return ("d30v");
	case EM_M32R: return ("Renesas M32R (formerly Mitsubishi M32r)");
	case EM_V800: return ("Renesas V850 (using RH850 ABI)");
	case EM_V850: return ("Renesas V850");
	default: return (get_machine2(elf_header));
	}
}

/**
 * get_machine2 - gets the target machine type string
 * @elf_header: address of elf header struct
 * Return: the string or NULL
 */
char *get_machine2(Elf64_Ehdr *elf_header)
{
	switch (elf_header->e_machine)
	{
	case EM_MN10300: return ("mn10300");
	case EM_MN10200: return ("mn10200");
	case EM_FR30: return ("Fujitsu FR30");
	case EM_PJ: return ("picoJava");
	case EM_MMA: return ("Fujitsu Multimedia Accelerator");
	case EM_PCP: return ("Siemens PCP");
	case EM_NCPU: return ("Sony nCPU embedded RISC processor");
	case EM_NDR1: return ("Denso NDR1 microprocesspr");
	case EM_STARCORE: return ("Motorola Star*Core processor");
	case EM_ME16: return ("Toyota ME16 processor");
	case EM_ST100: return ("STMicroelectronics ST100 processor");
	case EM_TINYJ: return ("Advanced Logic Corp. TinyJ embedded processor");
	case EM_PDSP: return ("Sony DSP processor");
	case EM_FX66: return ("Siemens FX66 microcontroller");
	case EM_ST9PLUS: return ("STMicroelectronics ST9+ 8/16 bit microcontroller");
	case EM_ST7: return ("STMicroelectronics ST7 8-bit microcontroller");
	case EM_68HC16: return ("Motorola MC68HC16 Microcontroller");
	case EM_68HC12: return ("Motorola MC68HC12 Microcontroller");
	case EM_68HC11: return ("Motorola MC68HC11 Microcontroller");
	case EM_68HC08: return ("Motorola MC68HC08 Microcontroller");
	case EM_68HC05: return ("Motorola MC68HC05 Microcontroller");
	case EM_SVX: return ("Silicon Graphics SVx");
	case EM_ST19: return ("STMicroelectronics ST19 8-bit microcontroller");
	case EM_VAX: return ("Digital VAX");
	case EM_AVR: return ("Atmel AVR 8-bit microcontroller");
	case EM_CRIS: return ("Axis Communications 32-bit embedded processor");
	case EM_JAVELIN: return ("Infineon Technologies 32-bit embedded cpu");
	case EM_FIREPATH: return ("Element 14 64-bit DSP processor");
	case EM_ZSP: return ("LSI Logic's 16-bit DSP processor");
	case EM_MMIX: return ("Donald Knuth's educational 64-bit processor");
	case EM_HUANY:
		return ("Harvard Universitys's machine-independent object format");
	case EM_PRISM: return ("Vitesse Prism");
	case EM_X86_64: return ("Advanced Micro Devices X86-64");
	case EM_S390: return ("IBM S/390");
	case EM_XTENSA: return ("Tensilica Xtensa Processor");
	default: return (NULL);
	}
}
