/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_buildindices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 19:24:56 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 13:00:21 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>

static int	extract_sections(t_bininfo const bi[1], t_ftvector vec[1],
								t_lc const *lc)
{
	size_t const	sec_size = SIZEOF_DYN(section, bi->arch);
	uint32_t		nsects;
	unsigned int	i;
	void const		*sect;

	nsects = ft_i32toh(ACCESS_SC(nsects, lc, bi->arch), bi->endian);
	sect = (void const*)lc + SIZEOF_DYN(segment_command, bi->arch);
	i = 0;
	while (i++ < nsects)
	{
		if (!nm_bin_ckaddr(bi, sect, sec_size))
			return (ERRORF("mmap overflow"));
		if (ftv_push_back(vec, &sect))
			return (ERRORNO("ftv_push_back"));
		sect = (void const *)sect + sec_size;
	}
	return (0);
}

/*
** LC_LOAD_DYLIB dylib_command
** LC_LOAD_WEAK_DYLIB dylib_command
** LC_REEXPORT_DYLIB dylib_command
** LC_LOAD_UPWARD_DYLIB (not dylib_command, but similar)
** LC_LAZY_LOAD_DYLIB (NOT HANDLED, NOT ENCOUNTERED)
*/

static uint32_t const	g_dylibs[] = {
	LC_LOAD_DYLIB, LC_LOAD_WEAK_DYLIB, LC_REEXPORT_DYLIB,
	LC_LOAD_UPWARD_DYLIB,
};

static int	read_lc(t_bininfo bi[1], t_lc const *lc, uint32_t cmd)
{
	unsigned int		i;

	if (cmd == LC_SEGMENT || cmd == LC_SEGMENT_64)
	{
		if (extract_sections(bi, bi->sects, lc))
			return (1);
	}
	else
	{
		i = 0;
		while (i < SIZE_ARRAY(g_dylibs))
		{
			if (cmd == g_dylibs[i])
				break ;
			i++;
		}
		if (i != SIZE_ARRAY(g_dylibs))
		{
			if (ftv_push_back(bi->dylibs, &lc))
				return (ERRORNO("ftv_push_back"));
		}
	}
	return (0);
}

int			nm_obj_buildindices(t_bininfo bi[1])
{
	size_t const	mh_size = SIZEOF_DYN(mach_header, bi->arch);
	uint32_t		ncmds;
	unsigned int	i;
	t_lc const		*lc;

	ncmds = ft_i32toh(ACCESS_MH(ncmds, bi->addr, bi->arch), bi->endian);
	if (!nm_bin_ckaddr(bi, bi->addr, mh_size))
		return (ERRORF("mmap overflow"));
	lc = bi->addr + mh_size;
	i = 0;
	while (i++ < ncmds)
	{
		if (!nm_bin_ckaddr(bi, lc, sizeof(*lc)))
			return (ERRORF("mmap overflow"));
		if (read_lc(bi, lc, ft_i32toh(lc->cmd, bi->endian)))
			return (1);
		lc = (void const*)lc + ft_i32toh(lc->cmdsize, bi->endian);
	}
	return (0);
}
