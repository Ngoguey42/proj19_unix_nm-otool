/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:12:02 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/09 19:18:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

/*
** mmap overflow verifications:
** all load_command			checked in nm_obj_buildsections
** all segment_command(_64)	checked in nm_obj_buildsections
** symtab_command			checking in nn1
*/

/*
** sections being indexed from 1, cur_file_sections[0] is a placeholder
*/

static int	print(t_env const e[1], t_objinfo const oi[1], void const *nl)
{
	t_syminfo	si[1];
	uint8_t		n_sect;

	// TODO assert addr
	// TODO assert string addr
	// TODO assert n_sect index
	n_sect = ACCESS_NL(n_sect, nl, oi->bi->arch);
	si->str = oi->strtab +
		ft_i32toh(ACCESS_NL_N_STRX(nl, oi->bi->arch), oi->bi->endian);
	si->n_type = ACCESS_NL(n_type, nl, oi->bi->arch);
	si->n_desc = ft_i16toh(ACCESS_NL(n_desc, nl, oi->bi->arch), oi->bi->endian);
	si->n_value = ft_i64toh(ACCESS_NL(n_value, nl, oi->bi->arch), oi->bi->endian);
	/* qprintf("%s\n", si->str); */
	return (0);
}

static int	nn2(t_env const e[1], t_objinfo oi[1], t_sc const *sc)
{
	void const			*nl;
	uint32_t const		nsyms = ft_i32toh(sc->nsyms, oi->bi->endian);
	size_t const		nl_size = SIZEOF_DYN(nlist, oi->bi->arch);
	unsigned int		i;

	nl = (void const*)oi->bi->addr + ft_i32toh(sc->symoff, oi->bi->endian);
	oi->strtab = (void const*)oi->bi->addr + ft_i32toh(sc->stroff, oi->bi->endian);
	i = 0;
	while (i++ < nsyms)
	{
		if (!nm_bin_ckaddr(oi->bi, nl, nl_size))
			return (ERRORF("mmap overflow"));
		/* qprintf("hello %d\n", i - 1); */
		print(e, oi, nl);
		nl = (void const*)nl + nl_size;
	}

	return (0);
}


static int	nn1(t_env const e[1], t_objinfo oi[1])
{
	size_t const	mh_size = SIZEOF_DYN(mach_header, oi->bi->arch);
	size_t			ncmds;
	unsigned int	i;
	int				tmp;
	t_lc const		*lc;

	ncmds = ft_i32toh(ACCESS_MH(ncmds, oi->bi->addr, oi->bi->arch), oi->bi->endian);
	lc = oi->bi->addr + mh_size;
	i = 0;
	while (i++ < ncmds)
	{
		if (ft_i32toh(lc->cmd, oi->bi->endian) == LC_SYMTAB)
		{
			if (!nm_bin_ckaddr(oi->bi, lc, sizeof(t_sc)))
				return (ERRORF("mmap overflow"));
			tmp = nn2(e, oi, (void const *)lc);
			break ;
		}
		lc = (void const*)lc + lc->cmdsize;
	}
	return (0);
}

int		nm_obj_handle(t_env const e[1], t_bininfo const bi[1])
{
	t_objinfo	oi[1];
	oi->bi = bi;

	ft_bzero(oi->sects, sizeof(t_ftvector));
	nm_obj_buildsections(bi, oi->sects);
	nn1(e, oi);
	ftv_release(oi->sects, NULL);
	return (0);
}
