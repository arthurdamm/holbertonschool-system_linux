#include "hreadelf.h"

/**
 * switch_all_endian_program - switches all endians if need be
 * @h: address of our internal struct
 * @i: index of this section
 */
void switch_all_endian_program(elf_t *h, size_t i)
{
	if (IS_BE(h->e64) && !IS_32(h->e64))
	{
		h->p64[i].p_type = switch_endian4(h->p64[i].p_type);
		h->p64[i].p_offset = switch_endian8(h->p64[i].p_offset);
		h->p64[i].p_vaddr = switch_endian8(h->p64[i].p_vaddr);
		h->p64[i].p_paddr = switch_endian8(h->p64[i].p_paddr);
		h->p64[i].p_filesz = switch_endian8(h->p64[i].p_filesz);
		h->p64[i].p_memsz = switch_endian8(h->p64[i].p_memsz);
		h->p64[i].p_align = switch_endian8(h->p64[i].p_align);
		h->p64[i].p_flags = switch_endian4(h->p64[i].p_flags);
	}
	if (IS_BE(h->e64) && IS_32(h->e64))
	{
		h->p32[i].p_type = switch_endian4(h->p32[i].p_type);
		h->p32[i].p_offset = switch_endian4(h->p32[i].p_offset);
		h->p32[i].p_vaddr = switch_endian4(h->p32[i].p_vaddr);
		h->p32[i].p_paddr = switch_endian4(h->p32[i].p_paddr);
		h->p32[i].p_filesz = switch_endian4(h->p32[i].p_filesz);
		h->p32[i].p_memsz = switch_endian4(h->p32[i].p_memsz);
		h->p32[i].p_align = switch_endian4(h->p32[i].p_align);
		h->p32[i].p_flags = switch_endian4(h->p32[i].p_flags);
	}
}

/**
 * switch_all_endian_symbol - switches all endians if need be
 * @h: address of our internal struct
 * @i: index of this section
 */
void switch_all_endian_symbol(elf_t *h, size_t i)
{
	if (IS_BE(h->e64) && !IS_32(h->e64))
	{
		
	}
	if (IS_BE(h->e64) && IS_32(h->e64))
	{

	}
	(void)i;
}
