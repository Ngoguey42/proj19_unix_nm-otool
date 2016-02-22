/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:12:02 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 14:10:32 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

/*
** mmap overflow verifications:
** all load_command			checked in nm_obj_buildsections
** all segment_command(_64)	checked in nm_obj_buildsections
** symtab_command			checked in nn1
** nlist					checked in nn2
** TODO
*/

/*
** sections being indexed from 1, cur_file_sections[0] is a placeholder
*/

static void	print_header(t_env const e[1], t_bininfo const bi[1])
{
	if (bi->membername.len != 0)
		ft_printf("\n%! $0.*hr(%! $0.*hr):\n",
					bi->pathname.len, bi->pathname.str,
					bi->membername.len, bi->membername.str);
	else if (bi->architecname.len != 0)
		ft_printf("\n%! $0.*hr (for architecture %! $0.*hr):\n",
					bi->pathname.len, bi->pathname.str,
					bi->architecname.len, bi->architecname.str);
	else if (e->paths.size > 1)
		ft_printf("\n%! $0.*hr:\n",
					bi->pathname.len, bi->pathname.str);
	return ;
}

static void	foreach_symbols(
	t_ftlist const *l, t_env const e[1], t_bininfo bi[1])
{
	t_ftlist_node	*node;

	if (e->opt & opt_r_revsort)
	{
		node = l->prev;
		while (node != ftl_cend(l))
		{
			nm_obj_printsym(e, bi, (const t_syminfo *)node);
			node = node->prev;
		}
	}
	else
	{
		node = l->next;
		while (node != ftl_cend(l))
		{
			nm_obj_printsym(e, bi, (const t_syminfo *)node);
			node = node->next;
		}
	}
	return ;
}

int			nm_obj_handle(t_env const e[1], t_bininfo bi[1])
{
	ftv_init_instance(bi->sects, sizeof(void const *));
	if (ftv_push_back(bi->sects, (void*[]){NULL}))
		return (ERRORNO("ftv_push_back"));
	ftv_init_instance(bi->dylibs, sizeof(void const *));
	if (ftv_push_back(bi->dylibs, (void*[]){NULL}))
		return (ERRORNO("ftv_push_back"));
	ftl_init_instance(bi->syms, sizeof(t_syminfo));
	if (nm_obj_buildindices(bi))
		return (1);
	if (nm_obj_symlist_build(e, bi))
		return (1);
	if (bi->syms->size > 0)
		print_header(e, bi);
	else
		ft_dprintf(2, "warning: ./ft_nm: no name list");
	foreach_symbols(bi->syms, e, bi);
	ftv_release(bi->sects, NULL);
	ftv_release(bi->dylibs, NULL);
	ftl_release(bi->syms, NULL);
	return (0);
}
