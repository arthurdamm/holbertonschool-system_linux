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
		h->y64[i].st_name = switch_endian4(h->y64[i].st_name);
		h->y64[i].st_shndx = switch_endian2(h->y64[i].st_shndx);
		h->y64[i].st_value = switch_endian8(h->y64[i].st_value);
		h->y64[i].st_size = switch_endian8(h->y64[i].st_size);
	}
	if (IS_BE(h->e64) && IS_32(h->e64))
	{
		h->y32[i].st_name = switch_endian4(h->y32[i].st_name);
		h->y32[i].st_shndx = switch_endian2(h->y32[i].st_shndx);
		h->y32[i].st_value = switch_endian4(h->y32[i].st_value);
		h->y32[i].st_size = switch_endian4(h->y32[i].st_size);
	}
	(void)i;
}

void switch_all_endian_ver(elf_t *h, uint16_t *versym, size_t versym_size,
	Elf64_Verneed *verneed, size_t verneed_size)
{
	size_t i = 0;

	if (!IS_BE(h->e64))
		return;

	for (i = 0; i < versym_size; i++)
		versym[i] = switch_endian2(versym[i]);
	for (i = 0; i < verneed_size; i++)
	{
		verneed[i].vn_version = switch_endian2(verneed[i].vn_version);
		verneed[i].vn_cnt = switch_endian2(verneed[i].vn_cnt);
		verneed[i].vn_file = switch_endian4(verneed[i].vn_file);
		verneed[i].vn_aux = switch_endian4(verneed[i].vn_aux);
		verneed[i].vn_next = switch_endian4(verneed[i].vn_next);
	}
	(void)versym;
}
