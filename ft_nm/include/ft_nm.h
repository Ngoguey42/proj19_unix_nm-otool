/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:19:52 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/04 05:02:29 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include "ft_debug.h"

typedef struct s_env			t_env;
struct			s_env
{
	int const					ac;
	char const *const *const	av;
};

t_env			nm_make_env(int ac, char const *const *av);

#endif
