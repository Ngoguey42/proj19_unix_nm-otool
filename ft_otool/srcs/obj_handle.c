/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:12:02 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 18:37:52 by ngoguey          ###   ########.fr       */
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
		ft_printf("%! $0.*hr(%! $0.*hr):\n",
					bi->pathname.len, bi->pathname.str,
					bi->membername.len, bi->membername.str);
	else if (bi->architecname.len != 0)
		ft_printf("%! $0.*hr (architecture %! $0.*hr):\n",
					bi->pathname.len, bi->pathname.str,
					bi->architecname.len, bi->architecname.str);
	else
		ft_printf("%! $0.*hr:\n",
					bi->pathname.len, bi->pathname.str);
	ft_putstr("(__TEXT,__text) section\n");
	(void)e;
	return ;
}

int			nm_obj_handle(t_env const e[1], t_bininfo bi[1])
{
	print_header(e, bi);
	if (nm_obj_dump_datasect(e, bi))
		return (1);
	return (0);
}
