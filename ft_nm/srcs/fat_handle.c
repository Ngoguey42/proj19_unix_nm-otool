/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 18:44:46 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 14:13:01 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/fat.h>
#include <sys/sysctl.h>
#include <mach-o/arch.h>
#include <stdlib.h>

struct s_cpu_name const	cpu[] = {
	(struct s_cpu_name){CPU_TYPE_I386, "i386"},
	(struct s_cpu_name){CPU_TYPE_X86_64, "x86_64"},
	(struct s_cpu_name){CPU_TYPE_POWERPC, "ppc"},
};

/*
** mmap overflow verifications:
** fat_header			size 8 or + checked in srcs/bin_readmagic.c
** fat_arch				in nm_fat_handle
** file size			in nm_fat_handle
*/

static int		sub_binary(
	t_env const e[1], t_bininfo fatbi[1], t_fatinfo fi[1], bool print_hdr)
{
	t_bininfo		bi[1];
	unsigned int	i;

	*bi = *fatbi;
	if (print_hdr)
	{
		i = 0;
		while (i < SIZE_ARRAY(cpu))
		{
			if (ft_i32toh(fi->hdr->cputype, bi->endian) == cpu[i].id)
				break ;
			i++;
		}
		if (i != SIZE_ARRAY(cpu))
			bi->architecname = (t_substr){cpu[i].str, ft_strlen(cpu[i].str)};
		else
			bi->architecname = (t_substr){"unknown", 7};
	}
	else
		bi->architecname = (t_substr){NULL, 0};
	bi->addr = fi->data;
	bi->st_size = fi->filesize;
	bi->addrend = bi->addr + bi->st_size;
	nm_bin_readmagic(bi);
	return (nm_bin_handle(e, bi));
}

static int		get_arch_index(
	t_bininfo const bi[1], t_fatinfo const fi[1],
	cpu_type_t local_cpu, cpu_subtype_t local_subcpu)
{
	unsigned int			i;
	enum e_nm_endian const	e = bi->endian;
	struct fat_arch const	*best;
	struct fat_arch			*cp;

	cp = ft_memdup(fi->hdr, fi->nfat_arch * sizeof(struct fat_arch));
	if (cp == NULL)
		return (-1);
	i = 0;
	while (i < fi->nfat_arch)
	{
		ft_uint_reorder(&cp[i].cputype, MEM_SIZEOF(t_fa, cputype), e);
		ft_uint_reorder(&cp[i].cpusubtype, MEM_SIZEOF(t_fa, cpusubtype), e);
		ft_uint_reorder(&cp[i].offset, MEM_SIZEOF(t_fa, offset), e);
		ft_uint_reorder(&cp[i].size, MEM_SIZEOF(t_fa, size), e);
		ft_uint_reorder(&cp[i].align, MEM_SIZEOF(t_fa, align), e);
		i++;
	}
	best = NXFindBestFatArch(local_cpu, local_subcpu, cp, fi->nfat_arch);
	free(cp);
	return ((best == NULL) ? -1 : best - cp);
}

static void		init_fatinfo(t_bininfo bi[1], t_fatinfo fi[1])
{
	size_t				size[1];
	size_t				tmp[1];
	int					err;
	NXArchInfo const	*local;

	fi->nfat_arch =
		ft_i32toh(((struct fat_header*)bi->addr)->nfat_arch, bi->endian);
	fi->hdr = bi->addr + sizeof(struct fat_header);
	*size = sizeof(*tmp);
	err = sysctlbyname("hw.cpu64bit_capable", tmp, size, NULL, 0);
	local = NXGetLocalArchInfo();
	if (err || local == NULL)
	{
		ERROR("Could not read local cpu info");
		fi->arch_index = -1;
	}
	else
		fi->arch_index = get_arch_index(
			bi, fi, local->cputype | ((*tmp) ? CPU_ARCH_ABI64 : 0),
			local->cpusubtype);
	return ;
}

static int		read_header(t_bininfo const bi[1], t_fatinfo fi[1])
{
	if (!nm_bin_ckaddr(bi, fi->hdr, sizeof(struct fat_arch)))
		return (ERRORF("mmap overflow"));
	fi->data = bi->addr + ft_i32toh(fi->hdr->offset, bi->endian);
	fi->filesize = ft_i32toh(fi->hdr->size, bi->endian);
	if (PRINT_DEBUG)
		ft_dprintf(2, "cpu%d subcpu%d off%d size%d align%d\n"
			, ft_i32toh(fi->hdr->cputype, bi->endian)
			, ft_i32toh(fi->hdr->cpusubtype, bi->endian)
			, fi->data - bi->addr
			, fi->filesize
			, ft_i32toh(fi->hdr->align, bi->endian));
	if (!nm_bin_ckaddr(bi, fi->data, fi->filesize))
		return (ERRORF("mmap overflow"));
	return (0);
}

int				nm_fat_handle(t_env const e[1], t_bininfo bi[1])
{
	t_fatinfo	fi[1];
	int			i;

	init_fatinfo(bi, fi);
	if (fi->arch_index >= 0)
	{
		fi->hdr += fi->arch_index;
		if (read_header(bi, fi) || sub_binary(e, bi, fi, false))
			return (1);
	}
	else
	{
		i = 0;
		while (i < (int)fi->nfat_arch)
		{
			if (read_header(bi, fi) || sub_binary(e, bi, fi, true))
				return (1);
			i++;
			fi->hdr++;
		}
	}
	return (0);
}
