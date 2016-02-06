/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:23:10 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/06 14:48:50 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ft_arg.h"

/*
** [-n -p -r] sorting flags
** [-g -u -U -j] quantity of colums/lines to display
** [-m] verbose SEG/SEC
*/

static int	save_option(unsigned int opt[1], char c)
{
	unsigned int	i;

	i = 0;
	while (i < ARG_NUM_OPTIONS)
	{
		if (ARG_OPTIONS[i] == c)
		{
			*opt |= 1 << i;
			return (0);
		}
		i++;
	}
	ft_dprintf(2, "error: ./ft_nm: invalid argument -%c\n%s\n", c, NM_USAGE);
	return (1);
}

static int	args(t_arg_parser p[1], unsigned int opt[1], t_ftvector files[1])
{
	enum e_arg		a;
	enum e_arg		expect;

	expect = FTARG_NONE;
	while ((a = ft_arg_next(p, expect)) != FTARG_NONE)
	{
		if (a == FTARG_OPTION)
		{
			if (save_option(opt, p->c))
				return (1);
		}
		else if (a == FTARG_STRING)
		{
			if (ftv_push_back(files, &p->s))
				return (ERRORNO("ftv_push_back"));
			expect = FTARG_STRING;
		}
	}
	return (0);
}

int			nm_make_env(int ac, char const *const *av, t_env e[1])
{
	unsigned int	opt[1];
	t_ftvector		files[1];

	if (ftv_init_instance(files, sizeof(char *)))
		return (ERRORNO("ftv_init_instance"));
	if (args((t_arg_parser[]){ft_arg_create(ac, av)}, opt, files))
		return (1);
	*e = (t_env){ac, av, *opt, *files, 0};
	return (0);
}
