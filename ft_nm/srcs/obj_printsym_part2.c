/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_printsym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 16:37:11 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 13:57:52 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include <unistd.h>

/*
**     if (libi >= (int)bi->dylibs->size)
**        return (0); //TODO: why return 0
*/

int		print_library(t_bininfo const bi[1], t_syminfo const si[1])
{
	int const	libi = GET_LIBRARY_ORDINAL(si->n_desc);
	void const	*ptr1;
	void const	*ptr2;
	size_t		size;

	if (libi >= (int)bi->dylibs->size)
		return (0);
	ptr1 = bi->dylibs->data;
	ptr1 = ((t_dc const *const *)ptr1)[libi];
	ptr1 = ptr1 + ft_i32toh(((t_dc const*)ptr1)->dylib.name.offset, bi->endian);
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

void	nm_obj_print_char2(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	if ((si->n_type & N_TYPE) == N_INDR)
		ft_printf(" (indirect for %s)", si->strtab + si->n_value);
	return ;
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
