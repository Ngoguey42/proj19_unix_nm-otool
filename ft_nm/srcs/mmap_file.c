/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 11:30:56 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 13:01:16 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <limits.h>
#include <errno.h>

/* static int	err(t_filename const *f, int errnum) */
/* { */
/* 	ft_printf("error: ./ft_nm: can's open file: %.*r (%s)\n", */
/* 			  f->file_len, f->file, ft_strerror(errnum)); */
/* 	return (1); */
/* } */


int		nm_file_make_mmapfilename(t_fileinfo f[1])
{
/* 	char		fname[PATH_MAX]; */
/* 	struct stat	stat[1]; */
/* 	int			err; */

/* 	if (f->file_len + 1 > PATH_MAX) */
/* 		return (err(f, ENAMETOOLONG)); */
/* 	ft_strlcpy(fname, f->file, f->file_len + 1); */
D/* 	*fd_dst = open(av[1], O_RDONLY); */
/* 	if (*fd_dst < 0) */
/* 		return (err(f, errno)); */
/* 	err = fstat(*fd_dst, stat); */
/* 	if (err != 0) */
/* 		return (err(f, errno)); */
/* 	*ptr_dst = mmap(NULL, buf->st_size, PROT_READ, MAP_PRIVATE, fd, 0); */
	return (0);
}
