/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_processpath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 16:12:49 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/09 16:25:31 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		nm_file_make_processpath(char const *file, t_substr *dst[2])
{
	char const *const	opparen = ft_strrchr(file, '(');
	size_t const		strlen = ft_strlen(file);
	size_t				filelen;

	if (strlen == 0 || file[strlen - 1] != ')' || opparen == NULL
		|| opparen == file)
	{
		*dst[0] = (t_substr){file, strlen};
		*dst[1] = (t_substr){NULL, 0};
		return ;
	}
	filelen = opparen - file;
	*dst[0] = (t_substr){file, filelen};
	*dst[1] = (t_substr){opparen + 1, strlen - filelen - 2};
	return ;
}
