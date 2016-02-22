/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_printsym_part1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 13:53:44 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 14:08:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <unistd.h>

#define SZ_SEC64 MEM_SIZEOF(struct section_64, sectname)
#define SZ_SEC32 MEM_SIZEOF(struct section, sectname)

#define SZ_SEG64 MEM_SIZEOF(struct section_64, segname)
#define SZ_SEG32 MEM_SIZEOF(struct section, segname)

#define SZ_BUF MAX(SZ_SEG64, SZ_SEG32) + MAX(SZ_SEC64, SZ_SEC32) + 5

/*
** n_desc:
** 0xff00		GET_LIBRARY_ORDINAL()
** 0x0080		N_WEAK_DEF and N_REF_TO_WEAK
** 0x0040		N_WEAK_REF
** 0x0020		N_NO_DEAD_STRIP and N_DESC_DISCARDED
** 0x0010		REFERENCED_DYNAMICALLY
** 0x0008		N_ARM_THUMB_DEF
** 0x0007		REFERENCE_TYPE
*/

char const		*g_ref_types[] = {
	[REFERENCE_FLAG_UNDEFINED_LAZY] = "(undefined [lazy bound]) ",
	[REFERENCE_FLAG_PRIVATE_DEFINED] = "(undefined [private]) "
};

static void		print_seg_sect(t_bininfo const bi[1], t_syminfo const si[1])
{
	char			buf[SZ_BUF];
	unsigned int	m;
	unsigned int	i;
	char const		*ptr;
	char			*ptrbuf;

	ft_strcpy(buf, "(");
	ptrbuf = buf + 1;
	m = bi->arch ? SZ_SEG64 : SZ_SEG32;
	ptr = ACCESS_SEC(segname, si->sect, bi->arch);
	i = 0;
	while (i++ < m && *ptr != '\0')
		*ptrbuf++ = *ptr++;
	*ptrbuf++ = ',';
	m = bi->arch ? SZ_SEC64 : SZ_SEC32;
	ptr = ACCESS_SEC(sectname, si->sect, bi->arch);
	i = 0;
	while (i++ < m && *ptr != '\0')
		*ptrbuf++ = *ptr++;
	*ptrbuf++ = ')';
	*ptrbuf = ' ';
	write(1, buf, ptrbuf - buf + 1);
	return ;
}

static void		toto(t_bininfo const bi[1], t_syminfo const si[1], char c)
{
	char	b[2];

	b[1] = ' ';
	if (si->n_type & N_EXT)
		b[0] = c;
	else
		b[0] = ft_tolower(c);
	write(1, b, 2);
	(void)bi;
	(void)si;
	return ;
}

#define CMP(str, ptr) (ft_strncmp(str, ptr, 16) == 0)

void			nm_obj_print_char1(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	if (si->n_value != 0 &&
		(si->n_type & N_TYPE) == N_UNDF &&
		si->n_type & N_EXT)
		write(1, "C ", 2);
	else if ((si->n_type & N_TYPE) == N_ABS)
		toto(bi, si, 'A');
	else if ((si->n_type & N_TYPE) == N_INDR)
		write(1, "I ", 2);
	else if ((si->n_type & N_TYPE) == N_SECT)
	{
		if (CMP(SECT_TEXT, ACCESS_SEC(sectname, si->sect, bi->arch)))
			toto(bi, si, 'T');
		else if (CMP(SECT_DATA, ACCESS_SEC(sectname, si->sect, bi->arch)))
			toto(bi, si, 'D');
		else if (CMP(SECT_BSS, ACCESS_SEC(sectname, si->sect, bi->arch)))
			toto(bi, si, 'B');
		else
			toto(bi, si, 'S');
	}
	else
		toto(bi, si, 'U');
	return ;
	(void)e;
}

static void		left_part(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	unsigned int i;

	if (si->n_value != 0
		&& (si->n_type & N_TYPE) == N_UNDF
		&& si->n_type & N_EXT)
		ft_printf("(common) (alignment 2^%u) ", GET_COMM_ALIGN(si->n_desc));
	else if ((si->n_type & N_TYPE) == N_ABS)
		ft_printf("(absolute) ");
	else if ((si->n_type & N_TYPE) == N_UNDF)
	{
		i = si->n_desc & REFERENCE_TYPE;
		if (i < SIZE_ARRAY(g_ref_types) && g_ref_types[i] != NULL)
			ft_putstr(g_ref_types[i]);
		else
			ft_printf("(undefined) ");
	}
	else if ((si->n_type & N_TYPE) == N_INDR)
		ft_putstr("(indirect) ");
	else
		print_seg_sect(bi, si);
	return ;
	(void)e;
}

void			nm_obj_print_mopt1(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	left_part(e, bi, si);
	if (si->n_desc & REFERENCED_DYNAMICALLY)
		ft_putstr("[referenced dynamically] ");
	if (si->n_desc & N_WEAK_REF
		|| (si->n_desc & N_WEAK_DEF && si->n_type & N_EXT))
		ft_putstr("weak ");
	if ((si->n_type & N_EXT) && (si->n_type & N_PEXT))
		ft_putstr("private external ");
	else if (si->n_type & N_EXT)
		ft_putstr("external ");
	else if (si->n_type & N_PEXT)
		ft_putstr("non-external (was a private external) ");
	else
		ft_putstr("non-external ");
	if ((si->n_desc & N_NO_DEAD_STRIP) && ((si->n_type & N_TYPE) == N_SECT))
		ft_putstr("[no dead strip] ");
	return ;
	(void)e;
}
