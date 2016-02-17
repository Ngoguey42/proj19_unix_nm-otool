/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_symlist_insert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 13:27:47 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/17 16:33:20 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

int				nm_obj_symlist_insert_popt(
	t_env const e[1], t_bininfo bi[1], t_syminfo const si[1])
{
	if (ftl_push_back(bi->syms, (void const *)si))
		return (ERROR("ftl_push_back"));
	return (0);
}

static int64_t	compare_str(t_syminfo const *a, t_syminfo const *b)
{
	return (ft_strcmp(a->str, b->str));
}

int				nm_obj_symlist_insert_noopt(
	t_env const e[1], t_bininfo bi[1], t_syminfo const si[1])
{
	if (ftl_insert_sort(bi->syms, (void const *)si, &compare_str))
		return (ERROR("ftl_push_back"));
	return (0);
}

static int64_t	compare_value(t_syminfo const *a, t_syminfo const *b)
{
	return (a->n_value - b->n_value);
}

int				nm_obj_symlist_insert_nopt(
	t_env const e[1], t_bininfo bi[1], t_syminfo const si[1])
{
	if (ftl_insert_sort(bi->syms, (void const *)si, &compare_value))
		return (ERROR("ftl_push_back"));
	return (0);
}
