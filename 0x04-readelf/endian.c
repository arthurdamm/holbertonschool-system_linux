#include "hreadelf.h"

/**
 * switch_endian2 - switches endianness on 2 byte unsigned int
 * @n: the unsigned int whose bytes to switch
 * Return: unsigned int with switched bytes
 */
unsigned short switch_endian2(unsigned short n)
{
	return (((n >> 8)  & 0x00ff) |
			((n << 8)  & 0xff00));
}

/**
 * switch_endian4 - switches endianness on 4 byte unsigned int
 * @n: the unsigned int whose bytes to switch
 * Return: unsigned int with switched bytes
 */
unsigned int switch_endian4(unsigned int n)
{
	return (((n >> 24) & 0x000000ff) |
			((n >> 8)  & 0x0000ff00) |
			((n << 8)  & 0x00ff0000) |
			((n << 24) & 0xff000000));
}

/**
 * switch_endian8 - switches endianness on 8 byte unsigned int
 * @n: the unsigned int whose bytes to switch
 * Return: unsigned int with switched bytes
 */
unsigned long switch_endian8(unsigned long n)
{
	return (((n >> 56) & 0x00000000000000ff) |
			((n >> 40) & 0x000000000000ff00) |
			((n >> 24) & 0x0000000000ff0000) |
			((n >> 8)  & 0x00000000ff000000) |
			((n << 8)  & 0x000000ff00000000) |
			((n << 24) & 0x0000ff0000000000) |
			((n << 40) & 0x00ff000000000000) |
			((n << 56) & 0xff00000000000000));
}

/**
 * switch_all_endian - switches all endians if need be
 * @h: address of our internal struct
 */
void switch_all_endian(elf_t *h)
{
	if (IS_BE(h->e64))
	{
		h->e64.e_machine = switch_endian2(h->e64.e_machine);
		h->e64.e_version = switch_endian4(h->e64.e_version);
		h->e64.e_flags = switch_endian4(h->e64.e_flags);
		h->e64.e_ehsize = switch_endian2(h->e64.e_ehsize);
		h->e64.e_phentsize = switch_endian2(h->e64.e_phentsize);
		h->e64.e_phnum = switch_endian2(h->e64.e_phnum);
		h->e64.e_shentsize = switch_endian2(h->e64.e_shentsize);
		h->e64.e_shnum = switch_endian2(h->e64.e_shnum);
		h->e64.e_shstrndx = switch_endian2(h->e64.e_shstrndx);
	}
	if (IS_BE(h->e64) && IS_32(h->e64))
	{
		h->e32.e_machine = switch_endian2(h->e32.e_machine);
		h->e32.e_version = switch_endian4(h->e32.e_version);
		h->e32.e_flags = switch_endian4(h->e32.e_flags);
		h->e32.e_ehsize = switch_endian2(h->e32.e_ehsize);
		h->e32.e_phentsize = switch_endian2(h->e32.e_phentsize);
		h->e32.e_phnum = switch_endian2(h->e32.e_phnum);
		h->e32.e_shentsize = switch_endian2(h->e32.e_shentsize);
		h->e32.e_shnum = switch_endian2(h->e32.e_shnum);
		h->e32.e_shstrndx = switch_endian2(h->e32.e_shstrndx);
	}
}
