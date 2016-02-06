/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:19:52 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/06 18:20:18 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include "ft_debug.h" //debug
# include "fterror.h"

# define ARG_OPTIONS "nprguUjm"
# define ARG_NUM_OPTIONS (sizeof(ARG_OPTIONS) - 1)
# define ARG_FIELD ((1 << ARG_NUM_OPTIONS) - 1)

# define NM_USAGE ("Usage: ./ft_nm [-" ARG_OPTIONS "] [file ...]")
# define NM_BOTHU "error: ./ft_nm: can't specifiy both -U and -u"
# define NM_INVARG "error: ./ft_nm: invalid argument -"

enum			e_nm_option
{
	opt_n_numsort = 0x01,
	opt_p_nosort = 0x02,
	opt_r_revsort = 0x04,
	opt_g_globonly = 0x08,
	opt_u_undefonly = 0x10,
	opt_U_noundef = 0x20,
	opt_j_symonly = 0x40,
	opt_m_verbose = 0x80
};

enum			e_nm_endian
{
	endian_little,
	endian_big
};

typedef struct s_env			t_env;
typedef struct s_filename		t_filename;

struct			s_filename
{
	char const					*file;
	char const					*member;
	uint32_t					file_len;
	uint32_t					member_len;
};

/*
** sections being indexed from 1, cur_file_sections[0] is a placeholder
*/
struct			s_env
{
	int const					ac;
	char const *const *const	av;
	unsigned int const			opt;
	t_ftvector const			files;

	int							cur_file_i;
	enum e_nm_endian			cur_file_endian;
	enum e_nm_endian			cur_obj_endian;
	t_ftvector					cur_obj_sections;

};

int				nm_make_env(int ac, char const *const *av, t_env e[1]);
int				nm_handle_file(t_env e[1], char const *filepath);

t_filename		nm_process_filename(char const *file);
int				nm_process_push_filename(t_ftvector v[1], char const *file);

#endif
