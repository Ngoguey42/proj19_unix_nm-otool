/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_printsym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 16:37:11 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/15 12:10:51 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include <unistd.h>


int		print_library(t_bininfo const bi[1], t_syminfo const si[1])
{
	char		buf[256];
	int const	libi = GET_LIBRARY_ORDINAL(si->n_desc);
	void const	*ptr1;
	void const	*ptr2;
	size_t		size;

	ptr1 = bi->dylibs->data;
	ptr1 = ((struct dylib_command const *const *)ptr1)[libi];
	ptr1 = ptr1 + ((struct dylib_command const *)ptr1)->dylib.name.offset;

	ptr2 = ft_strrchr(ptr1, '/');
	if (ptr2 != NULL)
		ptr1 = ptr2 + 1;

	ptr2 = ft_strchr(ptr1, '.');
	if (ptr2 != NULL)
		size = ptr2 - ptr1;
	else
		size = ft_strlen(ptr1);


	/* qprintf("%x\n", ((struct dylib_command const *)ptr)->dylib.name.offset); */
	/* qprintf("%s\n", ptr); */

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


int		nm_obj_printsym(t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{

	if (si->n_value == 0)
		ft_printf("%16s ", "");
	else
		ft_printf("%016llx ", si->n_value);
	if (si->sect == NULL)
		ft_printf("(undefined) ");
	else
	{
		print_seg_sect(bi, si);
		/* ft_printf("(%s,%s) " */
		/* 		  , ACCESS_SEC(segname, si->sect, bi->arch) */
		/* 		  , ACCESS_SEC(sectname, si->sect, bi->arch) */
		/* 	); */
	}
	if ((si->n_desc) & REFERENCED_DYNAMICALLY)
		ft_putstr("[referenced dynamically] ");
	if ((si->n_desc) & N_WEAK_REF)
		ft_putstr("weak ");



	if ((si->n_type) & N_EXT)
		ft_putstr("external ");
	else if (si->n_type & N_PEXT)
		ft_putstr("non-external (was a private external) ");
	else
		ft_putstr("non-external ");

	ft_dprintf(2, "%Is(pext%I1b type%I03b ext%I01b) ", "type"
			   , (si->n_type & N_PEXT) >> 4
			   , (si->n_type & N_TYPE) >> 1
			   , (si->n_type) & N_EXT
		);
	ft_dprintf(2, "%Js(%J011p) ", "sect", si->sect);
	ft_dprintf(2, "%Ks(%K#016b) ", "desc", si->n_desc);

	ft_putstr(si->str);

	if (GET_LIBRARY_ORDINAL(si->n_desc))
	{
		print_library(bi, si);
	}
	ft_putchar('\n');
	return (0);
}
