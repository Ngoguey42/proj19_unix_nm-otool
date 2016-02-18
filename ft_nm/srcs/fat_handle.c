/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 18:44:46 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/18 19:07:23 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/fat.h>
#include <sys/sysctl.h>

/*
** struct s_cpu_name const	cpu[] = {
** 	(struct s_cpu_name){CPU_TYPE_I386, "i386"},
** 	(struct s_cpu_name){CPU_TYPE_X86_64, "x86_64"},
** 	(struct s_cpu_name){CPU_TYPE_POWERPC, "ppc"},
** };
*/

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

/*
** static int		closest_arch(t_bininfo const bi[1], t_fatinfo const fi[1])
** {
** 	unsigned int			close_i;
** 	cpu_type_t				close_cpu;
** 	struct fat_arch const	*hdr;
** 	unsigned int			i;
** *
** 	close_i = 0;
** 	close_cpu = (cpu_type_t)ft_i32toh(fi->hdr->cputype, bi->endian);
** 	hdr = fi->hdr + 1;
** 	i = 0;
** 	while (++i < fi->nfat_arch)
** 	{
** 		if ((cpu_type_t)ft_i32toh(hdr->cputype, bi->endian) == fi->cpu)
** 		{
** 			if ((cpu_subtype_t)ft_i32toh(hdr->cpusubtype, bi->endian) ==
** 				fi->subcpu)
** 				return (i);
** 			else if (close_cpu != fi->cpu)
** 			{
** 				close_i = i;
** 				close_cpu = fi->cpu;
** 			}
** 		}
** 		hdr++;
** 	}
** 	return (close_cpu == fi->cpu ? close_i : -1);
** }
*/

static void		reorder_fat_arch(
	t_bininfo const bi[1], struct fat_arch *a, size_t const nfat_arch)
{
	unsigned int			i;
	enum e_nm_endian const	e = bi->endian;

	i = 0;
	while (i++ < nfat_arch)
	{
		ft_uint_reorder(&a->cputype, MEM_SIZEOF(t_fa, cputype), e);
		ft_uint_reorder(&a->cpusubtype, MEM_SIZEOF(t_fa, cpusubtype), e);
		ft_uint_reorder(&a->offset, MEM_SIZEOF(t_fa, offset), e);
		ft_uint_reorder(&a->size, MEM_SIZEOF(t_fa, size), e);
		ft_uint_reorder(&a->align, MEM_SIZEOF(t_fa, align), e);
		a++;
	}
	return ;
}

static void		init_fatinfo(t_bininfo bi[1], t_fatinfo fi[1])
{
	NXArchInfo const		*local;
	struct fat_arch const	*best;
	struct fat_arch			*copy;

	fi->nfat_arch =
		ft_i32toh(((struct fat_header*)bi->addr)->nfat_arch, bi->endian);
	fi->hdr = bi->addr + sizeof(struct fat_header);
	local = NXGetLocalArchInfo();
	if (local == NULL)
		fi->arch_index = -1;
		return ;
	copy = ft_memdup(fi->hdr, fi->nfat_arch * sizeof(struct fat_arch));
	if (copy == NULL)
	{
		fi->arch_index = -1;
		return ;
	}
	reorder_fat_arch(bi, copy, fi->nfat_arch);
	best = NXFindBestFatArch(local->cputype | CPU_ARCH_ABI64,
								local->cpusubtype, copy, fi->nfat_arch);
	fi->arch_index = best == NULL ? -1 : best - copy;
	free(copy);
	return ;
}

static int		read_header(t_bininfo const bi[1], t_fatinfo fi[1])
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
