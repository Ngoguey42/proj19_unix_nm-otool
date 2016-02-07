/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:23:10 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 12:55:07 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "ft_arg.h"

/*
** [-n -p -r] sorting flags
** [-g -u -U -j] quantity of colums/lines to display
** [-m] verbose SEG/SEC
** **
** -u enable -j (-u == -uj)
** -m disable -j (-m == -mj) (-mu == -muj)
*/

static char const *const g_default_file = "./a.out";

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
	ft_dprintf(2, "%s%c\n%s\n", NM_INVARG, c, NM_USAGE);
	return (1);
}

static int	args(t_arg_parser p[1], unsigned int opt[1], t_ftvector paths[1])
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

int			nm_env_make(int ac, char const *const *av, t_env e[1])
{
	unsigned int	opt[1];
	t_ftvector		paths[1];

	*opt = 0;
	if (ftv_init_instance(paths, sizeof(char *)))
		return (ERRORNO("ftv_init_instance"));
	if (args((t_arg_parser[1]){ft_arg_create(ac, av)}, opt, paths))
		return (1);
	if (paths->size == 0)
		if (ftv_push_back(paths, &g_default_file))
			return (ERRORNO("ftv_push_back"));
	if (*opt & opt_u_undefonly && *opt & opt_U_noundef)
	{
		ft_dprintf(2, "%s\n%s\n", NM_BOTHU, NM_USAGE);
		return (1);
	}
	if (*opt & opt_u_undefonly)
		*opt |= opt_j_symonly;
	if (*opt & opt_m_verbose)
		*opt &= ~opt_j_symonly;
	*e = (t_env){*opt & ARG_FIELD, *paths};
	return (0);
}
