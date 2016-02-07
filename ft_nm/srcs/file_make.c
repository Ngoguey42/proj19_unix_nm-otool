/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 12:14:49 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 14:50:26 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/fat.h>

#include "ft_nm.h"

static int	err(t_filename const f[1], char const *pb, int errnum)
{
	ft_printf("error: ./ft_nm: can't %s file: %.*r (%s)\n",
				pb, f->file_len, f->file, ft_strerror(errnum));
	return (1);
}

static int	open_f(t_fileinfo f[1])
{
	char	fpath[PATH_MAX];

	if (f->path.file_len + 1 > PATH_MAX)
		return (err(&f->path, "open", ENAMETOOLONG));
	ft_strlcpy(fpath, f->path.file, f->path.file_len + 1);
	f->fd = open(fpath, O_RDONLY);
	if (f->fd < 0)
		return (err(&f->path, "open", errno));
	return (0);
}

#define GREAT struct stat

static int	map_f(t_fileinfo f[1])
{
	int		e;
	GREAT	stat[1];

	e = fstat(f->fd, stat);
	if (e != 0)
		return (err(&f->path, "open", errno));
	f->st_size = stat->st_size;
	f->addr = mmap(NULL, stat->st_size, PROT_READ, MAP_PRIVATE, f->fd, 0);
	if (f->addr == MAP_FAILED)
		return (err(&f->path, "map", errno));
	return (0);
}

static void	read_magic(t_fileinfo f[1])
{
	uint32_t	m;

	f->type = unknown_file;
	if (f->st_size < 8)
		return ;
	m = *(uint32_t const *)f->addr;
	if (m == MH_MAGIC_64 || m == MH_MAGIC || m == MH_CIGAM_64 || m == MH_CIGAM)
		f->type = obj_file;
	else if (m == FAT_MAGIC || m == FAT_CIGAM)
		f->type = fat_file;
	else if (ft_strncmp("!<arch>", f->addr, 7) == 0)
		f->type = archive_file;
	else
		return ;
	if (m == MH_CIGAM_64 || m == MH_CIGAM || m == FAT_CIGAM)
		f->endian = endian_big;
	else
		f->endian = endian_little;
	if (m == MH_MAGIC_64 || m == MH_CIGAM_64)
		f->arch = arch_64b;
	else
		f->arch = arch_32b;
	return ;
}

int			nm_file_make(t_env const e[1], char const *path, t_fileinfo f[1])
{
	ft_bzero(f, sizeof(*f));
	f->addr = MAP_FAILED;
	f->fd = -1;
	f->path = nm_file_make_processpath(path);
	if (open_f(f))
		return (1);
	if (map_f(f))
		return (1);
	read_magic(f);
	return (0);
	(void)e;
}
