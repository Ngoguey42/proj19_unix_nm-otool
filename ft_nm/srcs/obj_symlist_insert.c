/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_symlist_insert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 13:27:47 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/17 14:21:27 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

int			nm_obj_symlist_insert(
	t_env const e[1], t_bininfo bi[1], t_syminfo const si[1])
{
	if (ftl_push_back(bi->syms, (void const *)si))
		return (ERROR("ftl_push_back"));
	return (0);
}
