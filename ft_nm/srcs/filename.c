/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 17:06:05 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/06 17:40:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int				nm_process_push_filename(t_ftvector v[1], char const *file)
{
	t_filename const f[1] = {nm_process_filename(file)};

	return (ftv_push_back(v, f));
}

t_filename		nm_process_filename(char const *file)
{
	char const *const	opparen = ft_strrchr(file, '(');
	size_t const		strlen = ft_strlen(file);
	size_t				filelen;

	if (strlen == 0 || file[strlen - 1] != ')'
		|| opparen == NULL || file[0] == '(')
		return ((t_filename){file, NULL, strlen, 0});
	filelen = opparen - file;
	return ((t_filename){file, opparen + 1,
				filelen, strlen - filelen - 2});
}
