/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_buildsections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:00:39 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 19:03:01 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>

static int	extract_sections(t_bininfo const bi[1], t_ftvector sects[1],
								t_lc const *lc)
{
	size_t const	sec_size = SIZEOF_DYN(section, bi->arch);
	uint32_t		nsects;
	unsigned int	i;
	void const		*sect;
	uint32_t		tmp32;

	nsects = ft_i32toh(ACCESS_SC(nsects, lc, bi->arch), bi->endian);
	sect = (void const*)lc + SIZEOF_DYN(segment_command, bi->arch);
	i = 0;
	while (i++ < nsects)
	{
		T;
		if (!nm_bin_ckaddr(bi, sect, sec_size))
			return (ERRORF("mmap overflow"));
		ft_printf("(%s,%s)\n"
				  , ACCESS_SEC(sectname, sect, bi->arch)
				  , ACCESS_SEC(segname, sect, bi->arch));
		if (ftv_push_back(sects, &sect))
			return (ERRORNO("ftv_push_back"));
		tmp32 = ft_i32toh(ACCESS_SEC(offset, sect, bi->arch), bi->endian);
		qprintf("tmp32 = %u\n", tmp32);
		sect = (void const *)sect + tmp32;
	}
	return (0);
}

int			nm_obj_buildsections(t_bininfo const bi[1], t_ftvector sects[1])
{
	size_t const	mh_size = SIZEOF_DYN(mach_header, bi->arch);
	uint32_t		ncmds;
	uint32_t		tmp32;
	unsigned int	i;
	t_lc const		*lc;

	ncmds = ft_i32toh(ACCESS_MH(ncmds, bi->addr, bi->arch), bi->endian);
	if (!nm_bin_ckaddr(bi, bi->addr, mh_size))
		return (ERRORF("mmap overflow"));
	if (ftv_init_instance(sects, sizeof(void const *)))
		return (ERRORNO("ftv_init_instance"));
	if (ftv_push_back(sects, (void*[]){NULL}))
		return (ERRORNO("ftv_push_back"));
	lc = bi->addr + mh_size;
	i = 0;
	while (i++ < ncmds)
	{
		T;
		if (!nm_bin_ckaddr(bi, lc, sizeof(*lc)))
			return (ERRORF("mmap overflow"));
		tmp32 = ft_i32toh(lc->cmd, bi->endian);
		if (tmp32 == LC_SEGMENT || tmp32 == LC_SEGMENT_64)
			if (extract_sections(bi, sects, lc))
				return (1);
		lc = (void const*)lc + lc->cmdsize;
	}
	return (0);
}
