/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:12:02 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/11 16:23:12 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

/*
** mmap overflow verifications:
** all load_command			checked in nm_obj_buildsections
** all segment_command(_64)	checked in nm_obj_buildsections
** symtab_command			checked in nn1
** nlist					checked in nn2
*/

/*
** sections being indexed from 1, cur_file_sections[0] is a placeholder
*/

static int	nn3(t_env const e[1], t_bininfo const bi[1],
				void const *nl, void const *strtab)
{
	t_syminfo	si[1];
	uint8_t		n_sect;

	n_sect = ACCESS_NL(n_sect, nl, bi->arch);
	if (n_sect >= bi->sects->size)
		return (ERRORF("sections index overflow"));
	si->str = strtab + ft_i32toh(ACCESS_NL_N_STRX(nl, bi->arch), bi->endian);
	if (!nm_bin_ckaddr(bi, strtab, sizeof(char)))
		return (ERRORF("mmap overflow"));
	si->n_type = ACCESS_NL(n_type, nl, bi->arch);
	si->n_desc = ft_i16toh(ACCESS_NL(n_desc, nl, bi->arch), bi->endian);
	si->n_value = ft_i64toh(ACCESS_NL(n_value, nl, bi->arch), bi->endian);
	/* qprintf("%s\n", si->str); */
	return (0);
}

static int	nn2(t_env const e[1], t_bininfo const bi[1], t_sc const *sc)
{
	void const			*nl;
	uint32_t const		nsyms = ft_i32toh(sc->nsyms, bi->endian);
	size_t const		nl_size = SIZEOF_DYN(nlist, bi->arch);
	unsigned int		i;
	char const			*strtab;

	nl = (void const*)bi->addr + ft_i32toh(sc->symoff, bi->endian);
	strtab = (void const*)bi->addr + ft_i32toh(sc->stroff, bi->endian);
	i = 0;
	while (i++ < nsyms)
	{
		if (!nm_bin_ckaddr(bi, nl, nl_size))
			return (ERRORF("mmap overflow"));
		/* qprintf("hello %d\n", i - 1); */
		ft_i32toh(ACCESS_NL_N_STRX(nl, bi->arch), bi->endian);
		nn3(e, bi, nl, strtab);
		nl = (void const*)nl + nl_size;
	}
	return (0);
}

static int	nn1(t_env const e[1], t_bininfo const bi[1])
{
	size_t const	mh_size = SIZEOF_DYN(mach_header, bi->arch);
	size_t			ncmds;
	unsigned int	i;
	int				tmp;
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
			tmp = nn2(e, bi, (void const *)lc);
			break ;
		}
		lc = (void const*)lc + lc->cmdsize;
	}
	return (0);
}

int		nm_obj_handle(t_env const e[1], t_bininfo bi[1])
{
	/* t_ftvector	bi->sects[1]; */
	/* t_objinfo	oi[1]; */
	/* bi = bi; */

	ft_bzero(bi->sects, sizeof(t_ftvector));
	nm_obj_buildsections(bi, bi->sects);
	nn1(e, bi);
	ftv_release(bi->sects, NULL);
	return (0);
}
