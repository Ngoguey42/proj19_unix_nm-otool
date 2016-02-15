/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acv_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 15:13:30 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/15 18:38:25 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
** mmap overflow verifications:
** archive header overflow	size 8 or + checked in srcs/bin_readmagic.c
** file header overflow		in nm_acv_read_header
** file name overflow		in nm_acv_read_header
** file size				in nm_acv_read_header
*/

static int	sub_binary(t_env const e[1], t_bininfo acvbi[1], t_acvinfo ai[1])
{
	t_bininfo	bi[1];

	*bi = *acvbi;
	bi->membername = ai->filename;
	bi->addr = ai->data;
	bi->st_size = ai->filesize;
	bi->addrend = bi->addr + bi->st_size;
	nm_bin_readmagic(bi);
	return (nm_bin_handle(e, bi));
}

int			nm_acv_handle(t_env const e[1], t_bininfo bi[1])
{
	t_acvinfo	ai[1];

	ai->hdr = bi->addr + 8;
	T;
	qprintf("begin%p end%p\n", ai->hdr, bi->addrend);
	while (ai->hdr < bi->addrend)
	{
		ft_dprintf(2, "60BYTES: %$M.60r \n", ai->hdr);
		if (nm_acv_read_header(bi, ai))
			return (0);
		ft_dprintf(2, "(%.*r) (%u)\n"
				   , ai->filename.len, ai->filename.str
				   , ai->filesize);
		(void)sub_binary(e, bi, ai);
		ai->hdr = ai->hdr + ai->filesize + 60;
	}
	return (0);
}
