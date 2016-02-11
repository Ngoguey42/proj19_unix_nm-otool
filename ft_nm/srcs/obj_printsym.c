/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_printsym.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 16:37:11 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/11 17:17:25 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

int		nm_obj_printsym(t_env const e[1], t_syminfo const si[1])
{
	if (si->n_value == 0)
		ft_printf("%16s ", "");
	else
		ft_printf("%016llx ", si->n_value);
	/* if (si->sect == NULL) */
		/* ft_printf("(%s)", "undefined"); */
	/* { */
	/* } */
	ft_printf("%Is(pext%I1b type%I03b ext%I01b) ", "type"
			  , (si->n_type >> 4) & N_PEXT
			  , (si->n_type >> 1) & N_TYPE
			  , (si->n_type) & N_EXT
		);
	ft_printf("%Js(%J011p) ", "sect", si->sect);
	ft_printf("%Ks(%K#016b) ", "desc", si->n_desc);
	ft_putendl(si->str);
	return (0);
}
