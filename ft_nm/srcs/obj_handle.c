/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:12:02 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 18:48:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		nm_obj_handle(t_env const e[1], t_bininfo bi[1])
{
	t_ftvector	sects[1];

	nm_obj_buildsections(bi, sects);
	return (0);
}
