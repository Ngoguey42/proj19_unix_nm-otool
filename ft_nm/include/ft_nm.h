/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:19:52 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/04 09:21:33 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include "ft_debug.h" //debug
# include "fterror.h"

# define ARG_OPTIONS "nprguUjm"
# define ARG_NUM_OPTIONS (sizeof(ARG_OPTIONS) - 1)

# define NM_USAGE ("Usage: ./ft_nm [-" ARG_OPTIONS "] [file ...]")

/* enum			e_nm_option */
/* { */
/* 	opt_n_numsort = 0, */
/* 	opt_p_nosort, */
/* 	opt_r_revsort, */
/* 	opt_g_globonly, */
/* 	opt_u_undefonly, */
/* 	opt_U_noundef, */
/* 	opt_j_symonly, */
/* 	opt_m_verbose */
/* }; */

typedef struct s_env			t_env;
struct			s_env
{
	int const					ac;
	char const *const *const	av;
	unsigned int const			opt;
	t_ftvector const			files;
};

int				nm_make_env(int ac, char const *const *av, t_env e[1]);

#endif
