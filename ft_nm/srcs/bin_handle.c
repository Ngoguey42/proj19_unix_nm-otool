/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:06:17 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/15 18:47:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

bool	nm_bin_ckaddr(t_bininfo const bi[1], void const *ptr, size_t s)
{
	if (ptr + s < bi->addrend)
		return (true);
	return (false);
}

static int	(*const g_handle_fn[])(t_env const[1], t_bininfo[1]) = {
	[unknown_file] = NULL,
	[obj_file] = &nm_obj_handle,
	[fat_file] = &nm_fat_handle,
	[archive_file] = &nm_acv_handle,
};

int		nm_bin_handle(t_env const e[1], t_bininfo bi[1])
{
	if (g_handle_fn[bi->type] != NULL)
		return (g_handle_fn[bi->type](e, bi));
	return (0);
}
