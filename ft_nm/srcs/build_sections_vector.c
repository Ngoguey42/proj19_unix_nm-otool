/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_sections_vector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 18:33:37 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 12:13:17 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <mach-o/loader.h>

/*
** TODO: Compiles but untested
*/

/* static int	extract_sections(t_env const e[1], t_ftvector sects[1], */
/* 								t_lc const *lc) */
/* { */
/* 	uint32_t const	nsects = ACCESS_SC(nsects, lc, e->obj_arch); */
/* 	unsigned int	i; */
/* 	void const		*sect; */

/* 	sect = (void const*)lc + SIZEOF_DYN(segment_command, e->obj_arch); */
/* 	i = 0; */
/* 	while (i++ < nsects) */
/* 	{ */
/* 		if (ftv_push_back(sects, &sect)) */
/* 			return (ERRORNO("ftv_push_back")); */
/* 		sect = (void const *)sect + ACCESS_SEC(size, sect, e->obj_arch); */
/* 	} */
/* 	return (0); */
/* } */

/* int			nm_build_obj_sections(t_env const e[1], t_ftvector sects[1]) */
/* { */
/* 	uint32_t const	ncmds = ACCESS_MH(ncmds, e->obj_ptr, e->obj_arch); */
/* 	unsigned int	i; */
/* 	t_lc const		*lc; */

/* 	if (ftv_init_instance(sects, sizeof(void const *))) */
/* 		return (ERRORNO("ftv_init_instance")); */
/* 	if (ftv_push_back(sects, (void*[]){NULL})) */
/* 		return (ERRORNO("ftv_push_back")); */
/* 	lc = e->obj_ptr + SIZEOF_DYN(mach_header, e->obj_arch); */
/* 	i = 0; */
/* 	while (i++ < ncmds) */
/* 	{ */
/* 		if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64) */
/* 			if (extract_sections(e, sects, lc)) */
/* 				return (1); */
/* 		lc = (void const*)lc + lc->cmdsize; */
/* 	} */
/* 	return (0); */
/* } */
