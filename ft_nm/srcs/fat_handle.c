/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 18:44:46 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/15 19:39:39 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>

#include "ft_nm.h"

#include <sys/sysctl.h>
/* #include <mach/machine.h> */

/*
** mmap overflow verifications:
** fat_header			size 8 or + checked in srcs/bin_readmagic.c
** fat_arch				in nm_fat_handle
** file size			??
*/

/* cpu_type_t  cputype;    /\* cpu specifier (int) *\/ */
/* cpu_subtype_t   cpusubtype; /\* machine specifier (int) *\/ */
/* uint32_t    offset;     /\* file offset to this object file *\/ */
/* uint32_t    size;       /\* size of this object file *\/ */
/* uint32_t    align;      /\* alignment as a power of 2 *\/ */


int				nm_fat_handle(t_env const e[1], t_bininfo bi[1])
{
	t_fatinfo		fi[1];
	uint32_t		nfat_arch;
	unsigned int	i;


    size_t size;
	cpu_type_t type;
	cpu_subtype_t subtype;
	size = sizeof(type);
	(void)sysctlbyname("hw.cputype", &type, &size, NULL, 0);
	size = sizeof(subtype);
	(void)sysctlbyname("hw.cpusubtype", &subtype, &size, NULL, 0);

	qprintf("types: %d %d \n", type, subtype);


	nfat_arch = ft_i32toh(((struct fat_header*)bi->addr)->nfat_arch, bi->endian);
	fi->hdr = bi->addr + sizeof(struct fat_header);
	i = 0;
	while (i < nfat_arch)
	{
		if (!nm_bin_ckaddr(bi, fi->hdr, sizeof(struct fat_arch)))
			return (ERRORF("mmap overflow"));
		fi->data = bi->addr + ft_i32toh(fi->hdr->offset, bi->endian);
		fi->filesize = ft_i32toh(fi->hdr->size, bi->endian);
		ft_dprintf(2, "cpu%d subcpu%d off%d size%d align%d\n"
				   , ft_i32toh(fi->hdr->cputype, bi->endian)
				   , ft_i32toh(fi->hdr->cpusubtype, bi->endian)
				   , fi->data - bi->addr
				   , fi->filesize
				   , ft_i32toh(fi->hdr->align, bi->endian)
			);
		if (!nm_bin_ckaddr(bi, fi->data, fi->filesize))
			return (ERRORF("mmap overflow"));
		/* if (!nm_bin_ckaddr(bi, ) */
		/* 	return (ERRORF("mmap overflow")); */
		i++;
		fi->hdr++;
	}
	return (0);
}
