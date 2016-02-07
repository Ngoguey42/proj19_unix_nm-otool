/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 12:14:49 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 13:03:15 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			nm_file_make(t_env const e[1], char const *path, t_fileinfo f[1])
{
	ft_bzero(f, sizeof(*f));
	f->path = nm_file_make_processpath(path);
	if (nm_file_make_mmapfilename(f))
		return (1); //TODO: determ retval
	return (0);
	(void)e;
}
