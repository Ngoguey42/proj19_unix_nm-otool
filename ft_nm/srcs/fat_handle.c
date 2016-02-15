/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 18:44:46 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/15 19:04:57 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>

#include "ft_nm.h"

/*
** mmap overflow verifications:
** fat_header			size 8 or + checked in srcs/bin_readmagic.c
** fat_arch				in nm_fat_handle
** file size			??
*/


int				nm_fat_handle(t_env const e[1], t_bininfo bi[1])
{
	t_fatinfo		fi[1];
	uint32_t		nfat_arch;
	unsigned int	i;

	nfat_arch = ft_i32toh(((struct fat_header*)bi->addr)->nfat_arch, bi->endian);
	fi->hdr = bi->addr + sizeof(struct fat_header);
	i = 0;
	while (i < nfat_arch)
	{
		T;

		i++;
		fi->hdr += sizeof(struct fat_arch);
	}
	return (0);
}
