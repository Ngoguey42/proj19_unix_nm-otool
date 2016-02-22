/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_release.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 14:44:20 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 17:54:31 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>

#include "ft_nm.h"

void	nm_file_release(t_fileinfo f[1])
{
	int		err;

	if (f->bi->addr != MAP_FAILED)
	{
		err = munmap((void*)f->bi->addr, f->bi->st_size);
		FT_ASSERT(err == 0);
	}
	if (f->fd >= 0)
	{
		err = close(f->fd);
		FT_ASSERT(err == 0);
	}
	return ;
}
