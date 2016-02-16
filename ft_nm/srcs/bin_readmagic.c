/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_readmagic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 17:51:25 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/16 16:55:38 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/fat.h>

#include "ft_nm.h"

void	nm_bin_readmagic(t_bininfo bi[1])
{
	uint32_t	m;

	/* qprintf("\t\t\tHELLO: \n"); */
	bi->type = unknown_file;
	if (bi->st_size < 8)
		return ;
	m = *(uint32_t const *)bi->addr;
	if (m == MH_MAGIC_64 || m == MH_MAGIC || m == MH_CIGAM_64 || m == MH_CIGAM)
		bi->type = obj_file;
	else if (m == FAT_MAGIC || m == FAT_CIGAM)
		bi->type = fat_file;
	else if (ft_memcmp("!<arch>\n", bi->addr, 8) == 0)
		bi->type = archive_file;
	else
		return ;
/* 	qprintf("\t\t\tDATA AT: %p\n", bi->addr); */

/* #define LOL(mac) if (m == mac) \ */
/* 		qprintf("\t\t\t%s\n", #mac) */

/* 	LOL( MH_CIGAM); */
/* 	LOL( MH_CIGAM_64); */
/* 	LOL( FAT_CIGAM); */
/* 	LOL( MH_MAGIC); */
/* 	LOL( MH_MAGIC_64); */
/* 	LOL( FAT_MAGIC); */

/* 	qprintf("\t\t\tARCH: %d\n", bi->type); */
	if (m == MH_CIGAM_64 || m == MH_CIGAM || m == FAT_CIGAM)
	{
		/* qprintf("\t\t\tBIG!!\n"); */
		bi->endian = endian_big;
	}
	else
	{
		/* qprintf("\t\t\tLITTLE!!\n"); */
		bi->endian = endian_little;
	}
	if (m == MH_MAGIC_64 || m == MH_CIGAM_64)
		bi->arch = arch_64b;
	else
		bi->arch = arch_32b;
	return ;
}
