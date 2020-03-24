#include "hreadelf.h"

#define MAPPING_TITLE \
	"\n Section to Segment mapping:\n  Segment Sections...\n"

#define ELF_SECTION_SIZE(sec_hdr, segment)			\
	(((sec_hdr->sh_flags & SHF_TLS) == 0				\
	|| sec_hdr->sh_type != SHT_NOBITS				\
	|| segment->p_type == PT_TLS) ? sec_hdr->sh_size : 0)

#define ELF_IS_SECTION_IN_SEGMENT(sec_hdr, segment)			\
	(((((sec_hdr->sh_flags & SHF_TLS) != 0)				\
	&& (segment->p_type == PT_TLS					\
	 || segment->p_type == PT_LOAD))				\
	|| ((sec_hdr->sh_flags & SHF_TLS) == 0				\
	&& segment->p_type != PT_TLS))					\
	&& (sec_hdr->sh_type == SHT_NOBITS					\
	|| (sec_hdr->sh_offset >= segment->p_offset		\
	   && (sec_hdr->sh_offset + ELF_SECTION_SIZE(sec_hdr, segment)	\
	       <= segment->p_offset + segment->p_filesz)))		\
	&& ((sec_hdr->sh_flags & SHF_ALLOC) == 0				\
	|| (sec_hdr->sh_addr >= segment->p_vaddr				\
	   && (sec_hdr->sh_addr + ELF_SECTION_SIZE(sec_hdr, segment)	\
	       <= segment->p_vaddr + segment->p_memsz))))

#define ELF_IS_SECTION_IN_SEGMENT_FILE(sec_hdr, segment)	\
	(sec_hdr->sh_size > 0						\
	&& ELF_IS_SECTION_IN_SEGMENT(sec_hdr, segment))

#define ELF_IS_SECTION_IN_SEGMENT_MEMORY(sec_hdr, segment)	\
	(ELF_SECTION_SIZE(sec_hdr, segment) > 0			\
	&& ELF_IS_SECTION_IN_SEGMENT(sec_hdr, segment))

/**
 * print_section_to_segment_mapping - self-documenting
 * @elf_header: the internal header
 * @string_table: the string table
 * Return: 0 on success else error
 */
int print_section_to_segment_mapping(elf_t *elf_header, char *string_table)
{
	size_t i, j;

	printf(MAPPING_TITLE);
	for (i = 0; i < EGET(e_phnum); i++)
	{
		printf("   %2.2lu     ", i);
		for (j = 0; j < EGET(e_shnum); j++)
		{
			if (IS_32(elf_header->e64))
			{
				if (ELF_IS_SECTION_IN_SEGMENT_MEMORY((&elf_header->s32[j]),
					(&elf_header->p32[i])))
					printf("%s ", string_table + SGET(j, sh_name));
			}
			else
			{
				if (ELF_IS_SECTION_IN_SEGMENT_MEMORY((&elf_header->s64[j]),
					(&elf_header->p64[i])))
					printf("%s ", string_table + SGET(j, sh_name));
			}
		}
		printf("\n");
	}
	return (0);
}
