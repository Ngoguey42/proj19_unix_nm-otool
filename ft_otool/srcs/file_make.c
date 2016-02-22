/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_make.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:24:54 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 16:43:04 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "ft_nm.h"

static int	err(t_substr const f[1], char const *pb, int errnum)
{
	ft_dprintf(2, "error: ./ft_otool: can't %s file: %.*r (%s)\n",
				pb, f->len, f->str, ft_strerror(errnum));
	return (1);
}

static int	open_f(t_fileinfo f[1])
{
	char	fpath[PATH_MAX];

	if (f->bi->pathname.len + 1 > PATH_MAX)
		return (err(&f->bi->pathname, "open", ENAMETOOLONG));
	ft_strlcpy(fpath, f->bi->pathname.str, f->bi->pathname.len + 1);
	f->fd = open(fpath, O_RDONLY);
	if (f->fd < 0)
		return (err(&f->bi->pathname, "open", errno));
	return (0);
}

#define GREAT struct stat

static int	map_f(t_fileinfo f[1])
{
	int		e;
	GREAT	stat[1];

	e = fstat(f->fd, stat);
	if (e != 0)
		return (err(&f->bi->pathname, "open", errno));
	f->bi->st_size = stat->st_size;
	f->bi->addr = mmap(NULL, stat->st_size, PROT_READ, MAP_PRIVATE, f->fd, 0);
	if (f->bi->addr == MAP_FAILED)
		return (err(&f->bi->pathname, "map", errno));
	f->bi->addrend = f->bi->addr + f->bi->st_size;
	return (0);
}

int			nm_file_make(t_env const e[1], char const *path, t_fileinfo f[1])
{
	ft_bzero(f, sizeof(*f));
	f->bi->addr = MAP_FAILED;
	f->fd = -1;
	nm_file_make_processpath(
		path, (t_substr*[2]){&f->bi->pathname, &f->bi->membername});
	if (open_f(f))
		return (1);
	if (map_f(f))
		return (1);
	nm_bin_readmagic(f->bi);
	return (0);
	(void)e;
}
