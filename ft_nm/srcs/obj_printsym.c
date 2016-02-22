/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_printsym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 16:37:11 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 13:58:09 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include <unistd.h>

void	nm_obj_print_debug(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	ft_dprintf(2, "%Is(pext%I1b type%I03b ext%I01b) ", "type"
		, (si->n_type & N_PEXT) >> 4
		, (si->n_type & N_TYPE) >> 1
		, si->n_type & N_EXT);
	ft_dprintf(2, "%Js(%J010p) ", "sect", si->sect);
	ft_dprintf(2, "%Ks(lib%#0K4x 8bit%K1b weak%K1b 6bit%K1b"
		" dynref%K1b thumb%K1b ref%K03b) ", "desc"
		, GET_LIBRARY_ORDINAL(si->n_desc)
		, (si->n_desc & N_WEAK_DEF) >> 7
		, (si->n_desc & N_WEAK_REF) >> 6
		, (si->n_desc & N_NO_DEAD_STRIP) >> 5
		, (si->n_desc & REFERENCED_DYNAMICALLY) >> 4
		, (si->n_desc & N_ARM_THUMB_DEF) >> 3
		, (si->n_desc & REFERENCE_TYPE));
	return ;
	(void)e;
	(void)bi;
}

int		nm_obj_printsym(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	if (PRINT_DEBUG)
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
