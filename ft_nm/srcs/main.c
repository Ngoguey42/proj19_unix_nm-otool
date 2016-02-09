/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:19:24 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/09 16:26:36 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	scroll_paths(t_env const e[1])
{
	char const *const	*p;
	char const *const	*pend;
	t_fileinfo			f[1];

	p = e->paths.data;
	pend = e->paths.data + sizeof(char *) * e->paths.size;
	ftv_print(&e->paths, "s");
	while (p < pend)
	{
		if (nm_file_make(e, *p, f) == 0)
		{
			ft_dprintf(2, "%M45.*r with %J-15.*r"
					   "size(%u) type(%hhu) end(%hhu) arch(%hhu)\n"
					   , f->path.len, f->path.str
					   , f->bi->member.len, f->bi->member.str
					   , f->bi->st_size , f->bi->type
					   , f->bi->endian, f->bi->arch
				); // debug
			if (nm_bin_handle(e, f->bi) == 0)
			{

			}
		}
		nm_file_release(f);
		p++;
	}
	return (0);
}

int			main(int ac, char *av[])
{
	t_env				e[1];

	PRINTSIZEOF(t_fileinfo);
	PRINTSIZEOF(t_bininfo);
	if (nm_env_make(ac, (char const *const *)av, e))
		return (1);
	ft_dprintf(2, "flags: %I#.*b\n", ARG_NUM_OPTIONS, e->opt);
	if (scroll_paths(e))
		return (1);
	return (0);
}
