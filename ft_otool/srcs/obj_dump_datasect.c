/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_dump_datasect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 17:03:49 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 18:22:21 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>

#define SZ_SEC64 MEM_SIZEOF(struct section_64, sectname)
#define SZ_SEC32 MEM_SIZEOF(struct section, sectname)

#define SZ_SEG64 MEM_SIZEOF(struct section_64, segname)
#define SZ_SEG32 MEM_SIZEOF(struct section, segname)

static int	dump_text_section(
	t_env const e[1], t_bininfo bi[1], void const *sect)
{
	void const	*ptr;
	uint64_t	addr;
	uint64_t	size;
	int			i;

	ptr = bi->addr + ft_i32toh(ACCESS_SEC(offset, sect, bi->arch), bi->endian);
	if (bi->arch)
		addr = ft_i64toh(ACCESS_SEC(addr, sect, bi->arch), bi->endian);
	else
		addr = ft_i32toh(ACCESS_SEC(addr, sect, bi->arch), bi->endian);
	if (bi->arch)
		size = ft_i64toh(ACCESS_SEC(size, sect, bi->arch), bi->endian);
	else
		size = ft_i32toh(ACCESS_SEC(size, sect, bi->arch), bi->endian);
	while (size > 0)
	{
		ft_printf("%0*llx ", bi->arch ? 16 : 8, addr);
		i = 0;
		while (i++ < 16 && size > 0)
		{
			ft_printf("%02hhx ", *(char*)ptr++);
			size--;
		}
		ft_putchar('\n');
		addr += 16;
	}
	return (0);
}

static bool	scroll_sections(t_env const e[1], t_bininfo bi[1], void const *sc)
{
	size_t const	sec_size = SIZEOF_DYN(section, bi->arch);
	uint32_t		nsects;
	unsigned int	i;
	void const		*sect;

	nsects = ft_i32toh(ACCESS_SC(nsects, sc, bi->arch), bi->endian);
	sect = (void const*)sc + SIZEOF_DYN(segment_command, bi->arch);
	i = 0;
	while (i++ < nsects)
	{
		if (!nm_bin_ckaddr(bi, sect, sec_size))
			return (ERRORF("mmap overflow"));
		if (!ft_strncmp(SECT_TEXT, ACCESS_SEC(sectname, sect, bi->arch), 16)
			&& !ft_strncmp(SEG_TEXT, ACCESS_SEC(segname, sect, bi->arch), 16))
		{
			(void)dump_text_section(e, bi, sect);
			return (true);
		}
		sect = (void const *)sect + sec_size;
	}
	return (false);
}

int			nm_obj_dump_datasect(t_env const e[1], t_bininfo bi[1])
{
	size_t const	mh_size = SIZEOF_DYN(mach_header, bi->arch);
	uint32_t		ncmds;
	unsigned int	i;
	t_lc const		*lc;
	uint32_t		cmd;

	ncmds = ft_i32toh(ACCESS_MH(ncmds, bi->addr, bi->arch), bi->endian);
	if (!nm_bin_ckaddr(bi, bi->addr, mh_size))
		return (ERRORF("mmap overflow"));
	lc = bi->addr + mh_size;
	i = 0;
	while (i++ < ncmds)
	{
		if (!nm_bin_ckaddr(bi, lc, sizeof(*lc)))
			return (ERRORF("mmap overflow"));
		cmd = ft_i32toh(lc->cmd, bi->endian);
		if (cmd == LC_SEGMENT || cmd == LC_SEGMENT_64)
		{
			if (scroll_sections(e, bi, lc))
				break ;
		}
		lc = (void const*)lc + ft_i32toh(lc->cmdsize, bi->endian);
	}
	return (0);
}
