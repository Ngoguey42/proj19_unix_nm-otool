/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:19:24 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 14:49:59 by ngoguey          ###   ########.fr       */
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
		/* ft_dprintf(2, "%M15.*r with %J-15.*r\n" */
		/* 		   , fn->file_len, fn->file, fn->member_len, fn->member); // debug */
		if (nm_file_make(e, *p, f))
		{


		}
		nm_file_release(f);
		/* if (nm_handle_file(e, NULL)) */
		/* 	return (1); */
		/* e->file_i++; */
		p++;
	}
	return (0);
}

int			main(int ac, char *av[])
{
	t_env				e[1];

	if (nm_env_make(ac, (char const *const *)av, e))
		return (1);
	ft_dprintf(2, "flags: %I#.*b\n", ARG_NUM_OPTIONS, e->opt);
	if (scroll_paths(e))
		return (1);
	return (0);
}
