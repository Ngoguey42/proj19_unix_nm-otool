/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 18:44:46 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/16 13:52:41 by ngoguey          ###   ########.fr       */
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

static int		sub_binary(
	t_env const e[1], t_bininfo fatbi[1], t_fatinfo fi[1])
{
	t_bininfo	bi[1];

	*bi = *fatbi;
	/* bi->membername = ai->filename; */
	bi->addr = fi->data;
	bi->st_size = fi->filesize;
	bi->addrend = bi->addr + bi->st_size;
	nm_bin_readmagic(bi);
	return (nm_bin_handle(e, bi));
}

static int		closest_arch(t_bininfo const bi[1], t_fatinfo const fi[1])
{
	unsigned int			close_i;
	cpu_type_t				close_cpu;
	struct fat_arch const	*hdr;
	unsigned int			i;

	close_i = 0;
	close_cpu = (cpu_type_t)ft_i32toh(fi->hdr->cputype, bi->endian);
	hdr = fi->hdr + 1;
	i = 0;
	while (++i < fi->nfat_arch)
	{
 		if ((cpu_type_t)ft_i32toh(hdr->cputype, bi->endian) == fi->cpu)
		{
			if ((cpu_subtype_t)ft_i32toh(hdr->cpusubtype, bi->endian) == fi->subcpu)
				return (i);
			else if (close_cpu != fi->cpu)
			{
				close_i = i;
				close_cpu = fi->cpu;
			}
		}
		hdr++;
	}
	return (close_cpu == fi->cpu ? close_i : -1);
}

static void		init_fatinfo(t_bininfo bi[1], t_fatinfo fi[1])
{
	size_t	size[1];
	size_t	tmp[1];

	*size = sizeof(cpu_type_t);
	(void)sysctlbyname("hw.cputype", &fi->cpu, size, NULL, 0);
	*size = sizeof(cpu_subtype_t);
	(void)sysctlbyname("hw.cpusubtype", &fi->subcpu, size, NULL, 0);
	*tmp = 0;
	*size = sizeof(size_t);
	(void)sysctlbyname("hw.cpu64bit_capable", tmp, size, NULL, 0);
	if (*tmp)
		fi->cpu |= CPU_ARCH_ABI64;
	qprintf("types: %d %d \n", fi->cpu, fi->subcpu);
	fi->nfat_arch =
		ft_i32toh(((struct fat_header*)bi->addr)->nfat_arch, bi->endian);
	fi->hdr = bi->addr + sizeof(struct fat_header);
	return ;
}

int				nm_fat_handle(t_env const e[1], t_bininfo bi[1])
{
	t_fatinfo		fi[1];
	unsigned int	i;

	init_fatinfo(bi, fi);
	if (fi->nfat_arch == 0)
		return (0);
	i = closest_arch(bi, fi);
	qprintf("truclol: %d\n", i);
	i = 0;
	while (i < fi->nfat_arch)
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
		/* sub_binary(e, bi, fi); */
		/* if (!nm_bin_ckaddr(bi, ) */
		/* 	return (ERRORF("mmap overflow")); */
		i++;
		fi->hdr++;
	}
	return (0);
}
