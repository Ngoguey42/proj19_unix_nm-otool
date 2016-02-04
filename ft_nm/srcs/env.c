/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:23:10 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/04 05:14:18 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ft_arg.h"

t_env	nm_make_env(int ac, char const *const* av)
{
	enum e_arg a;
	t_arg_parser p[1];
	int was_c = 0;
	int was_n = 0;

	*p = ft_arg_create(ac, av);
	do
	{
		qprintf("\n");
		if (was_c)
			a = ft_arg_next(p, FTARG_INT);
		else if (was_n)
			a = ft_arg_next(p, FTARG_STRING);
		else
			a = ft_arg_next(p, FTARG_NONE);
		was_c = 0;
		was_n = 0;
		qprintf("ARG=%s (%d)\n", ft_arg_name(a), a);

		if (a == FTARG_STRING)
			qprintf("\tstr=%s\n", p->s);
		if (a == FTARG_OPTION)
		{
			qprintf("\topt=%c\n", p->c);
			if (p->c == 'c')
				was_c = 1;
			if (p->c == 'n')
				was_n = 1;
		}
		if (a == FTARG_INT)
			qprintf("\tint=%d\n", p->i);
	} while (a != FTARG_NONE);

	return ((t_env){ac, av});
}
