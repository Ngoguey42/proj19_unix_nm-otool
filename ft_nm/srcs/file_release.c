/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_release.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 14:44:20 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 14:46:37 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <sys/mman.h>

void	nm_file_release(t_fileinfo f[1])
{
	int		err;

	if (f->addr != MAP_FAILED)
	{
		err = munmap(f->addr, f->st_size);
		FT_ASSERT(err == 0);
	}
	if (f->fd >= 0)
	{
		err = close(f->fd);
		FT_ASSERT(err == 0);
	}
	return ;
}
