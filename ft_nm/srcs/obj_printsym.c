/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_printsym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 16:37:11 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/17 16:44:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include <unistd.h>

int		print_library(t_bininfo const bi[1], t_syminfo const si[1])
{
	int const	libi = GET_LIBRARY_ORDINAL(si->n_desc);
	void const	*ptr1;
	void const	*ptr2;
	size_t		size;

	if (libi >= (int)bi->dylibs->size)
		return (0); //TODO: why return 0
	ptr1 = bi->dylibs->data;
	ptr1 = ((struct dylib_command const *const *)ptr1)[libi];
	ptr1 = ptr1 +
		ft_i32toh(
			((struct dylib_command const *)ptr1)->dylib.name.offset
			, bi->endian
			);
	if (!nm_bin_ckaddr(bi, ptr1, sizeof(char)))
		return (ERRORF("mmap overflow"));

	ptr2 = ft_strrchr(ptr1, '/');
	if (ptr2 != NULL)
		ptr1 = ptr2 + 1;

	size = ft_strcspn(ptr1, "._");

	ft_putstr(" (from ");
	write(1, ptr1, size);
	ft_putchar(')');
	return (0);
}

#define SZ_SEC64 MEM_SIZEOF(struct section_64, sectname)
#define SZ_SEC32 MEM_SIZEOF(struct section, sectname)

#define SZ_SEG64 MEM_SIZEOF(struct section_64, segname)
#define SZ_SEG32 MEM_SIZEOF(struct section, segname)

#define SZ_BUF MAX(SZ_SEG64, SZ_SEG32) + MAX(SZ_SEC64, SZ_SEC32) + 5

static void	print_seg_sect(t_bininfo const bi[1], t_syminfo const si[1])
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

char const *ref_types[] = {
	[REFERENCE_FLAG_UNDEFINED_LAZY] = "(undefined [lazy bound]) ",
	[REFERENCE_FLAG_PRIVATE_DEFINED] = "(undefined [private]) "
};

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

void	nm_obj_print_value(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	if ((si->n_type & N_TYPE) != N_INDR &&
		(
			(si->n_type & N_TYPE) == N_SECT
			|| (si->n_desc & REFERENCED_DYNAMICALLY)
			|| ((si->n_type & N_TYPE) == N_ABS)
			/* || si->n_value != 0 */
			))
		ft_printf("%0*llx ", bi->arch ? 16 : 8, si->n_value);
	else
		ft_printf("%*s ", bi->arch ? 16 : 8, "");
	return ;
	(void)e;
}

/* (si->n_type & N_EXT) */

static void	toto(
	t_bininfo const bi[1], t_syminfo const si[1], char c)
{
	char 	b[2];

	b[1] = ' ';
	if (si->n_type & N_EXT)
		b[0] = c;
	else
		b[0] = ft_tolower(c);
	write(1, b, 2);
	return ;
}

static bool	cmp(char const *str, void const *ptr)
{
	return (ft_strncmp(str, ptr, 16) == 0);
}

void	nm_obj_print_char1(
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
		if (cmp(SECT_TEXT, ACCESS_SEC(sectname, si->sect, bi->arch)))
			toto(bi, si, 'T');
		else if (cmp(SECT_DATA, ACCESS_SEC(sectname, si->sect, bi->arch)))
			toto(bi, si, 'D');
		else if (cmp(SECT_BSS, ACCESS_SEC(sectname, si->sect, bi->arch)))
			toto(bi, si, 'B');
		else
			toto(bi, si, 'S');
	}
	else
		toto(bi, si, 'U');
	return ;
}

void	nm_obj_print_char2(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	if ((si->n_type & N_TYPE) == N_INDR)
		ft_printf(" (indirect for %s)", si->strtab + si->n_value);
	return ;
}
void	nm_obj_print_mopt1(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	unsigned int i;

	if (si->n_value != 0 && (si->n_type & N_TYPE) == N_UNDF && si->n_type & N_EXT)
		ft_printf("(common) (alignment 2^%u) ", GET_COMM_ALIGN(si->n_desc));
	else if ((si->n_type & N_TYPE) == N_ABS)
		ft_printf("(absolute) ");
	else if ((si->n_type & N_TYPE) == N_UNDF)
	{
		i = si->n_desc & REFERENCE_TYPE;
		if (i < SIZE_ARRAY(ref_types) && ref_types[i] != NULL)
			ft_putstr(ref_types[i]);
		else
			ft_printf("(undefined) ");
	}
	else if ((si->n_type & N_TYPE) == N_INDR)
		ft_putstr("(indirect) ");
	else
		print_seg_sect(bi, si);


	if (si->n_desc & REFERENCED_DYNAMICALLY)
		ft_putstr("[referenced dynamically] ");

	if (si->n_desc & N_WEAK_REF
		|| (si->n_desc & N_WEAK_DEF && si->n_type & N_EXT)
		)
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

void	nm_obj_print_debug(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	ft_dprintf(2, "%Is(pext%I1b type%I03b ext%I01b) ", "type"
			   , (si->n_type & N_PEXT) >> 4
			   , (si->n_type & N_TYPE) >> 1
			   , si->n_type & N_EXT
		);
	ft_dprintf(2, "%Js(%J010p) ", "sect", si->sect);
	ft_dprintf(2, "%Ks(lib%#0K4x 8bit%K1b weak%K1b 6bit%K1b"
			   " dynref%K1b thumb%K1b ref%K03b) ", "desc"
			   , GET_LIBRARY_ORDINAL(si->n_desc)
			   , (si->n_desc & N_WEAK_DEF) >> 7
			   , (si->n_desc & N_WEAK_REF) >> 6
			   , (si->n_desc & N_NO_DEAD_STRIP) >> 5
			   , (si->n_desc & REFERENCED_DYNAMICALLY) >> 4
			   , (si->n_desc & N_ARM_THUMB_DEF) >> 3
			   , (si->n_desc & REFERENCE_TYPE)
		);
	return ;
	(void)e;
	(void)bi;
}

int		nm_obj_print_mopt2(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	if ((si->n_type & N_TYPE) == N_INDR)
		ft_printf(" (for %s)", si->strtab + si->n_value);
	if (GET_LIBRARY_ORDINAL(si->n_desc) == DYNAMIC_LOOKUP_ORDINAL)
		ft_putstr(" (dynamically looked up)");
	else if (GET_LIBRARY_ORDINAL(si->n_desc))
	{
		if (print_library(bi, si))
			return (1);
	}
	return (0);
	(void)e;
}

int		nm_obj_printsym(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	nm_obj_print_debug(e, bi, si);
	nm_obj_print_value(e, bi, si);
	if (e->opt & opt_m_verbose)
		nm_obj_print_mopt1(e, bi, si);
	else
		nm_obj_print_char1(e, bi, si);

	ft_putstr(si->str);
	if (e->opt & opt_m_verbose)
	{
		if (nm_obj_print_mopt2(e, bi, si))
			return (1);
	}
	else
		nm_obj_print_char2(e, bi, si);
	ft_putchar('\n');
	return (0);
}
