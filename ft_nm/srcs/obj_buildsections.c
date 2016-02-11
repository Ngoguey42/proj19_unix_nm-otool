/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_buildsections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:00:39 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/11 19:07:28 by ngoguey          ###   ########.fr       */
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
		/* ft_printf("(%s,%s)\n" */
		/* 		  , ACCESS_SEC(segname, sect, bi->arch) */
		/* 		  , ACCESS_SEC(sectname, sect, bi->arch)); */
		if (ftv_push_back(vec, &sect))
			return (ERRORNO("ftv_push_back"));
		sect = (void const *)sect + sec_size;
	}
	return (0);
}

int			nm_obj_buildsections(t_bininfo const bi[1], t_ftvector vec[1])
{
	size_t const	mh_size = SIZEOF_DYN(mach_header, bi->arch);
	uint32_t		ncmds;
	uint32_t		tmp32;
	unsigned int	i;
	t_lc const		*lc;

	ncmds = ft_i32toh(ACCESS_MH(ncmds, bi->addr, bi->arch), bi->endian);
	if (!nm_bin_ckaddr(bi, bi->addr, mh_size))
		return (ERRORF("mmap overflow"));
	ftv_init_instance(vec, sizeof(void const *));
	if (ftv_push_back(vec, (void*[]){NULL}))
		return (ERRORNO("ftv_push_back"));
	lc = bi->addr + mh_size;
	i = 0;
	while (i++ < ncmds)
	{
		if (!nm_bin_ckaddr(bi, lc, sizeof(*lc)))
			return (ERRORF("mmap overflow"));
		tmp32 = ft_i32toh(lc->cmd, bi->endian);
		if (tmp32 == LC_SEGMENT || tmp32 == LC_SEGMENT_64)
			if (extract_sections(bi, vec, lc))
				return (1);
		lc = (void const*)lc + lc->cmdsize;
	}
	return (0);
}
