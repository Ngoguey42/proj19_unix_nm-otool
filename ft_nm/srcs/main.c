/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:19:24 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/06 17:41:00 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		main(int ac, char *av[])
{
	t_env				e[1];
	t_filename const 	*f;
	t_filename const	*fend;

	if (nm_make_env(ac, (char const *const *)av, e))
		return (1);
	f = e->files.data;
	fend = e->files.data + sizeof(t_filename) * e->files.size;
	ft_dprintf(2, "flags: %I#.*b\n", ARG_NUM_OPTIONS, e->opt);
	ftv_print(&e->files, "ssuu");
	while (f < fend)
	{
		ft_dprintf(2, "%M15.*r with %J-15.*r\n"
				   , f->file_len, f->file, f->member_len, f->member); // debug
		if (nm_handle_file(e, NULL))
			return (1);
		e->cur_file_id++;
		f++;
	}
	return (0);
}
