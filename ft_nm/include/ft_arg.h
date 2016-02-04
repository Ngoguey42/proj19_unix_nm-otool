/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 03:53:42 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/04 04:33:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARG_H
# define FT_ARG_H

# include "libft.h"

/*
** 0      1  2    3   4     5  6
** ./truc -l -lac -12 salut -n name
** 012345 01 0123 012 01234 01 0123
** *
** stri	chari	call
** 0	5		(NONE)->ret:FTARG_OPTION c:l
** 1	1		(NONE)->ret:FTARG_OPTION c:l
** 2	1		(NONE)->ret:FTARG_OPTION c:a
** 2	2		(NONE)->ret:FTARG_OPTION c:c
** 2	3		(INT)->ret:FTARG_INT i:-12
** 3	2		(NONE)->ret:FTARG_STRING str:@salut
** 4	4		(NONE)->ret:FTARG_OPTION c:n
** 5	1		(STRING)->ret:FTARG_STRING str:@name
** 6	3		(NONE)->ret:FTARG_NONE
** 		'expected' parameter is used to disambiguate strings beginning with
** a minus, and negative integers
*/

typedef struct s_arg_parser	t_arg_parser;

struct			s_arg_parser
{
	char const					*s;
	char						c;
	int							i;

	int const					priv_ac;
	unsigned int				priv_stri;
	unsigned int				priv_chari;
	char const *const *const	priv_av;
};

enum			e_arg
{
	FTARG_OPTION,
	FTARG_STRING,
	FTARG_INT,
	FTARG_NONE
};

t_arg_parser	ft_arg_create(int ac, char const *const *av);
enum e_arg		ft_arg_next(enum e_arg expected);

#endif
