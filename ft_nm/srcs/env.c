/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:23:10 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/06 15:10:22 by ngoguey          ###   ########.fr       */
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
	if (args((t_arg_parser[1]){ft_arg_create(ac, av)}, opt, files))
		return (1);
	if (files->size == 0)
		if (ftv_push_back(files, &g_default_file))
			return (ERRORNO("ftv_push_back"));
	if (*opt & opt_u_undefonly)
		*opt |= opt_j_symonly;
	if (*opt & opt_m_verbose)
		*opt &= ~opt_j_symonly;
	*e = (t_env){ac, av, *opt, *files, 0, 0, 0};
	return (0);
}
