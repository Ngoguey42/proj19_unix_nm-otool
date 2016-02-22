/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_build_symlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 12:25:55 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 13:02:34 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

static int	read_nlist(
	t_env const e[1], t_bininfo const bi[1], void const *nl, t_syminfo si[1])
{
	uint8_t		n_sect;

	si->n_type = ACCESS_NL(n_type, nl, bi->arch);
	if ((si->n_type & N_STAB) != 0)
		return (0);
	si->str = si->strtab +
		ft_i32toh(ACCESS_NL_N_STRX(nl, bi->arch), bi->endian);
	if (!nm_bin_ckaddr(bi, si->str, sizeof(char)))
		return (ERRORF("mmap overflow"));
	n_sect = ACCESS_NL(n_sect, nl, bi->arch);
	if (n_sect >= bi->sects->size)
		return (ERRORF("sections index overflow"));
	si->sect = ((void const *const *)bi->sects->data)[n_sect];
	si->n_desc = ft_i16toh(ACCESS_NL(n_desc, nl, bi->arch), bi->endian);
	if (bi->arch)
		si->n_value = ft_i64toh(ACCESS_NL(n_value, nl, bi->arch), bi->endian);
	else
		si->n_value = ft_i32toh(ACCESS_NL(n_value, nl, bi->arch), bi->endian);
	return (0);
}

static int	scroll_symbols(t_env const e[1], t_bininfo bi[1], t_sc const *sc)
{
	uint32_t const	nsyms = ft_i32toh(sc->nsyms, bi->endian);
	size_t const	nl_size = SIZEOF_DYN(nlist, bi->arch);
	void const		*nl;
	t_syminfo		si[1];
	unsigned int	i;

	nl = (void const*)bi->addr + ft_i32toh(sc->symoff, bi->endian);
	si->strtab = (void const*)bi->addr + ft_i32toh(sc->stroff, bi->endian);
	if (!nm_bin_ckaddr(bi, si->strtab, sizeof(char)))
		return (ERRORF("mmap overflow"));
	i = 0;
	while (i++ < nsyms)
	{
		if (!nm_bin_ckaddr(bi, nl, nl_size))
			return (ERRORF("mmap overflow"));
		si->str = NULL;
		if (read_nlist(e, bi, nl, si))
			return (1);
		if (si->str != NULL && e->sym_insert(e, bi, si))
			return (1);
		nl = (void const*)nl + nl_size;
	}
	return (0);
}

int			nm_obj_symlist_build(t_env const e[1], t_bininfo bi[1])
{
	size_t const	mh_size = SIZEOF_DYN(mach_header, bi->arch);
	size_t			ncmds;
	unsigned int	i;
	t_lc const		*lc;

	ncmds = ft_i32toh(ACCESS_MH(ncmds, bi->addr, bi->arch), bi->endian);
	lc = bi->addr + mh_size;
	i = 0;
	while (i++ < ncmds)
	{
		if (ft_i32toh(lc->cmd, bi->endian) == LC_SYMTAB)
		{
			if (!nm_bin_ckaddr(bi, lc, sizeof(t_sc)))
				return (ERRORF("mmap overflow"));
			if (scroll_symbols(e, bi, (void const *)lc))
				return (1);
		}
		lc = (void const*)lc + ft_i32toh(lc->cmdsize, bi->endian);
	}
	return (0);
}
