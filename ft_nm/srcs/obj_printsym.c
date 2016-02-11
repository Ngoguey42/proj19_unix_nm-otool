/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_printsym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 16:37:11 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/11 19:08:01 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

int		nm_obj_printsym(t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	if (si->n_value == 0)
		ft_printf("%16s ", "");
	else
		ft_printf("%016llx ", si->n_value);
	if (si->sect == NULL)
		ft_printf("(undefined) ");
	else
		ft_printf("(%s,%s) "
				  , ACCESS_SEC(segname, si->sect, bi->arch)
				  , ACCESS_SEC(sectname, si->sect, bi->arch)
			);
	if ((si->n_desc) & REFERENCED_DYNAMICALLY)
		ft_putstr("[referenced dynamically] ");
	if ((si->n_type) & N_EXT)
		ft_putstr("external ");
	else
		ft_putstr("non-external ");

	ft_dprintf(2, "%Is(pext%I1b type%I03b ext%I01b) ", "type"
			  , (si->n_type >> 4) & N_PEXT
			  , (si->n_type >> 1) & N_TYPE
			  , (si->n_type) & N_EXT
		);
	ft_dprintf(2, "%Js(%J011p) ", "sect", si->sect);
	ft_dprintf(2, "%Ks(%K#016b) ", "desc", si->n_desc);

	ft_putstr(si->str);

	if (GET_LIBRARY_ORDINAL(si->n_desc))
		ft_putstr(" (from )");
	ft_putchar('\n');
	return (0);
}
