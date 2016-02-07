/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:12:02 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 19:49:01 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
** mmap overflow verifications:
** all load_command			checked in nm_obj_buildsections
** all segment_command(_64)	checked in nm_obj_buildsections
*/

/*
** sections being indexed from 1, cur_file_sections[0] is a placeholder
*/

int		nm_obj_handle(t_env const e[1], t_bininfo bi[1])
{
	t_ftvector	sects[1];

	ft_bzero(sects, sizeof(*sects));
	nm_obj_buildsections(bi, sects);
	ftv_release(sects, NULL);
	return (0);
}
