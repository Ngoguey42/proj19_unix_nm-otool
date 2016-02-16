/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_printsym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 16:37:11 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/16 14:50:54 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include <unistd.h>

/* static size_t  ft_strcspn_n(const char *s1r, const char *s2r, size_t size) */
/* { */
/* 	const char *s1 = s1r; */
/* 	const char *s2; */

/* 	while (*s1 && size-- > 0) */
/* 	{ */
/* 		s2 = s2r; */
/* 		while (*s2) */
/* 		{ */
/* 			if (*s1 == *s2++) */
/* 				return (s1 - s1r); */
/* 		} */
/* 		s1++; */
/* 	} */
/* 	return (s1 - s1r); */
/* } */

int		print_library(t_bininfo const bi[1], t_syminfo const si[1])
{
	int const	libi = GET_LIBRARY_ORDINAL(si->n_desc);
	void const	*ptr1;
	void const	*ptr2;
	size_t		size;

	if (libi >= (int)bi->dylibs->size)
		return (0);
	ptr1 = bi->dylibs->data;
	ptr1 = ((struct dylib_command const *const *)ptr1)[libi];
	ptr1 = ptr1 + ((struct dylib_command const *)ptr1)->dylib.name.offset;
	if (!nm_bin_ckaddr(bi, ptr1, sizeof(char)))
		return (ERRORF("mmap overflow"));

	ptr2 = ft_strrchr(ptr1, '/');
	if (ptr2 != NULL)
		ptr1 = ptr2 + 1;

	size = ft_strcspn(ptr1, "._");
	/* ptr2 = ft_strchr(ptr1, '.'); */
	/* if (ptr2 != NULL) */
	/* 	size = ptr2 - ptr1; */
	/* else */
	/* 	size = ft_strlen(ptr1); */

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


int		nm_obj_printsym(t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	(void)e;
	unsigned int i;


	if ((si->n_type & N_TYPE) == N_SECT
		|| (si->n_desc) & REFERENCED_DYNAMICALLY
		|| si->n_value != 0)
		ft_printf("%0*llx ", bi->arch ? 16 : 8, si->n_value);
	else
		ft_printf("%*s ", bi->arch ? 16 : 8, "");

/*
  0000000100016fa0 (__TEXT,__text) non-external (was a private external)
  ___clang_call_terminate

0000000100016fa0 (__TEXT,__text) weak non-external (was a private external)
type(pext1 type111 ext0)
sect(0x10c5150b0)
desc(lib0000 8bit1 weak0 6bit0 dynref0 thumb0 ref000)
___clang_call_terminate

 */

	if (si->n_value != 0 && (si->n_type & N_TYPE) == N_UNDF && si->n_type & N_EXT)
		ft_printf("(common) (alignment 2^%u) ", GET_COMM_ALIGN(si->n_desc));
	else if (((si->n_type) & N_TYPE) == N_ABS)
		ft_printf("(absolute) ");
	else if (((si->n_type) & N_TYPE) == N_UNDF)
	{
		i = si->n_desc & REFERENCE_TYPE;
		if (i < SIZE_ARRAY(ref_types) && ref_types[i] != NULL)
			ft_putstr(ref_types[i]);
		else
			ft_printf("(undefined) ");
	}
	else
		print_seg_sect(bi, si);

	if ((si->n_desc) & REFERENCED_DYNAMICALLY)
		ft_putstr("[referenced dynamically] ");

	if (si->n_desc & N_WEAK_REF
		|| (si->n_desc & N_WEAK_DEF && !(si->n_type & N_PEXT)))
		ft_putstr("weak ");



	if ((si->n_type) & N_EXT)
		ft_putstr("external ");
	else if (si->n_type & N_PEXT)
		ft_putstr("non-external (was a private external) ");
	else
		ft_putstr("non-external ");
	if (si->n_desc & N_NO_DEAD_STRIP)
		ft_putstr("[no dead strip] ");

	ft_dprintf(2, "%Is(pext%I1b type%I03b ext%I01b) ", "type"
			   , (si->n_type & N_PEXT) >> 4
			   , (si->n_type & N_TYPE) >> 1
			   , (si->n_type) & N_EXT
		);
	ft_dprintf(2, "%Js(%J010p) ", "sect", si->sect);
	ft_dprintf(2, "%Ks(lib%#0K4x 8bit%K1b weak%K1b 6bit%K1b dynref%K1b thumb%K1b ref%K03b) ", "desc"
			   /* , si->n_desc */
			   , GET_LIBRARY_ORDINAL(si->n_desc)
			   , (si->n_desc & N_WEAK_DEF) >> 7
			   , (si->n_desc & N_WEAK_REF) >> 6
			   , (si->n_desc & N_NO_DEAD_STRIP) >> 5
			   , (si->n_desc & REFERENCED_DYNAMICALLY) >> 4
			   , (si->n_desc & N_ARM_THUMB_DEF) >> 3
			   , (si->n_desc & REFERENCE_TYPE)
		);

	ft_putstr(si->str);

	if (GET_LIBRARY_ORDINAL(si->n_desc))
		print_library(bi, si);
	ft_putchar('\n');
	return (0);
}
