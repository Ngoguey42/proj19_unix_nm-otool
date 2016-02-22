/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_printsym_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 13:52:36 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 14:04:18 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/nlist.h>

void	nm_obj_print_value(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1])
{
	if ((si->n_type & N_TYPE) != N_INDR &&
		(
			(si->n_type & N_TYPE) == N_SECT
			|| (si->n_desc & REFERENCED_DYNAMICALLY)
			|| ((si->n_type & N_TYPE) == N_ABS)
			|| si->n_value != 0))
		ft_printf("%0*llx ", bi->arch ? 16 : 8, si->n_value);
	else
		ft_printf("%*s ", bi->arch ? 16 : 8, "");
	return ;
	(void)e;
}
