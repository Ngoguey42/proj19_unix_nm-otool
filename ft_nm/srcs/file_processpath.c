/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_processpath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 16:12:49 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 16:12:49 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_filename		nm_file_make_processpath(char const *file)
{
	char const *const	opparen = ft_strrchr(file, '(');
	size_t const		strlen = ft_strlen(file);
	size_t				filelen;

	if (strlen == 0 || file[strlen - 1] != ')' || opparen == NULL)
		return ((t_filename){file, NULL, strlen, 0});
	filelen = opparen - file;
	return ((t_filename){file, opparen + 1,
				filelen, strlen - filelen - 2});
}
