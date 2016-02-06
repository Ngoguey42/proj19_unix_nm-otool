/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:19:24 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/06 14:47:40 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		main(int ac, char *av[])
{
	t_env		e[1];
	char const	**filepath;
	char const	**filepathend;

	if (nm_make_env(ac, (char const *const *)av, e))
		return (1);
	filepath = e->files.data;
	filepathend = e->files.data + sizeof(char *) * e->files.size;
	while (filepath < filepathend)
	{
		qprintf("%s\n", *filepath);
		if (nm_handle_file(e, *filepath))
			return (1);
		e->cur_file_id++;
		filepath++;
	}
	return (0);
}
