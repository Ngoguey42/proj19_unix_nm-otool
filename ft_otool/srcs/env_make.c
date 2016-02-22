/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 14:53:13 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 16:46:34 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ft_arg.h"

static int		save_option(unsigned int opt[1], char c)
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
	ft_dprintf(2, "%s%c\n%s\n", NM_INVARG, c, NM_USAGE);
	return (1);
}

static int		args(
	t_arg_parser p[1], unsigned int opt[1], t_ftvector paths[1])
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
			if (ftv_push_back(paths, &p->s))
				return (ERRORNO("ftv_push_back"));
			expect = FTARG_STRING;
		}
	}
	return (0);
}

static void		*get_sym_insert_fn(unsigned int opt)
{
	if (opt & opt_n_numsort)
		return (&nm_obj_symlist_insert_nopt);
	else if (opt & opt_p_nosort)
		return (&nm_obj_symlist_insert_popt);
	else
		return (&nm_obj_symlist_insert_noopt);
}

int				nm_env_make(int ac, char const *const *av, t_env e[1])
{
	unsigned int	opt[1];
	t_ftvector		paths[1];

	*opt = 0;
	ftv_init_instance(paths, sizeof(char *));
	if (args((t_arg_parser[1]){ft_arg_create(ac, av)}, opt, paths))
		return (1);
	if (paths->size == 0)
		ft_dprintf(2, "%s\n%s\n", NM_NOFILE, NM_USAGE);
	*e = (t_env){*opt & ARG_FIELD, *paths, get_sym_insert_fn(*opt)};
	return (0);
}
