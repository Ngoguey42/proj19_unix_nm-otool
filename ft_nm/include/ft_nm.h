/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:19:52 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/07 13:01:48 by ngoguey          ###   ########.fr       */
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

# define ACCESS32B(s,f,p) ( ((struct s const*)(p))->f )
# define ACCESS64B(s,f,p) ( ((struct s ## _64 const*)(p))->f )
# define ACCESS(s,f,p,a) ((a) == arch_32b ? ACCESS32B(s,f,p) : ACCESS64B(s,f,p))

# define ACCESS_MH(f,p,a) ACCESS(mach_header, f, p, a)
# define ACCESS_SC(f,p,a) ACCESS(segment_command, f, p, a)
# define ACCESS_SEC(f,p,a) ACCESS(section, f, p, a)
# define SIZEOF_DYN(s,a) ((a)==arch_32b?sizeof(struct s):sizeof(struct s##_64))

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
	endian_little = 0,
	endian_big
};

enum			e_nm_arch
{
	arch_32b = 0,
	arch_64b
};

typedef struct load_command		t_lc;

typedef struct s_env			t_env;
typedef struct s_filename		t_filename;
typedef struct s_fileinfo		t_fileinfo;

struct			s_filename
{
	char const					*file;
	char const					*member;
	uint32_t					file_len;
	uint32_t					member_len;
};

struct			s_fileinfo
{
	t_filename					path;

	int							fd;

	void const					*addr;
	size_t						st_size;

	enum e_nm_endian			endian;
	enum e_nm_arch				arch;
};

/*
** sections being indexed from 1, cur_file_sections[0] is a placeholder
*/
struct			s_env
{
	unsigned int				opt;
	t_ftvector					paths;

	/* t_fileinfo					*curf; */
	/* t_objinfo const				*curo; */


	/* enum e_nm_endian			obj_endian; */
	/* enum e_nm_arch				obj_arch; */
	/* void const					*obj_ptr; */
	/* size_t						obj_size; */
	/* t_ftvector					obj_sections; */

};

int				nm_env_make(int ac, char const *const *av, t_env e[1]);
int				nm_file_make(t_env const e[1], char const *p, t_fileinfo f[1]);


t_filename		nm_file_make_processpath(char const *file);
int				nm_file_make_mmapfilename(t_fileinfo f[1]);

/* int				nm_build_obj_sections(t_env const e[1], t_ftvector sects[1]); */
/* int				nm_handle_file(t_env e[1], char const *filepath); */

#endif
