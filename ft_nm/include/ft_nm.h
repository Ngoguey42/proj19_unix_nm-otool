/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 02:19:52 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/22 12:48:26 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

#include <mach/machine.h> //delete ?
#include <mach-o/arch.h>

# include "libft.h"
# include "ft_list.h"
# include "ft_debug.h" //debug
# include "fterror.h"

# define PRINT_DEBUG true

# define ARG_OPTIONS "nprguUjm"
# define ARG_NUM_OPTIONS (sizeof(ARG_OPTIONS) - 1)
# define ARG_FIELD ((1 << ARG_NUM_OPTIONS) - 1)

# define NM_USAGE ("Usage: ./ft_nm [-" ARG_OPTIONS "] [file ...]")
# define NM_BOTHU "error: ./ft_nm: can't specifiy both -U and -u"
# define NM_INVARG "error: ./ft_nm: invalid argument -"

# define ACCESS32B(s,f,p) ( ((struct s const*)(p))->f )
# define ACCESS64B(s,f,p) ( ((struct s ## _64 const*)(p))->f )
# define ACCESS(s,f,p,a) ((a) == arch_32b ? ACCESS32B(s,f,p) : ACCESS64B(s,f,p))

# define _N_STRX32(p) ((struct nlist const*)(p))->n_un.n_strx
# define _N_STRX64(p) ((struct nlist_64 const*)(p))->n_un.n_strx

# define ACCESS_MH(f,p,a) ACCESS(mach_header, f, p, a)
# define ACCESS_SC(f,p,a) ACCESS(segment_command, f, p, a)
# define ACCESS_SEC(f,p,a) ACCESS(section, f, p, a)
# define ACCESS_NL(f,p,a) ACCESS(nlist, f, p, a)
# define ACCESS_NL_N_STRX(p,a) ((a) == arch_32b ? _N_STRX32(p) : _N_STRX64(p))
# define SIZEOF_DYN(s,a) ((a)==arch_32b?sizeof(struct s):sizeof(struct s##_64))

# define MEM_SIZEOF(type, member) sizeof(((type *)0)->member)

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

enum			e_nm_bintype
{
	unknown_file = 0,
	obj_file,
	fat_file,
	archive_file,
};

typedef struct load_command		t_lc;
typedef struct symtab_command	t_sc;
typedef struct fat_arch			t_fa;


typedef struct s_env			t_env;
typedef struct s_substr			t_substr;
typedef struct s_fileinfo		t_fileinfo;
typedef struct s_bininfo		t_bininfo;
typedef struct s_syminfo		t_syminfo;
typedef struct s_acvinfo		t_acvinfo;
typedef struct s_fatinfo		t_fatinfo;

/*
** t_filename					is itself a t_bininfo
** t_bininfo					is one of e_nm_bintype
** e_nm_bintype::unknown_file	is a terminal bin
** e_nm_bintype::obj_file		is a terminal bin
** e_nm_bintype::fat_file		may contain several bin
** e_nm_bintype::archive_file	may contain several bin
*/

struct			s_substr
{
	char const					*str;
	size_t						len;
};

struct			s_cpu_name
{
	uint32_t					id;
	char						*str;
};

struct			s_bininfo
{
	t_substr					pathname;
	t_substr					membername;
	t_substr					architecname;

	void const					*addr;
	void const					*addrend;
	size_t						st_size;

	enum e_nm_bintype			type:8;
	enum e_nm_endian			endian:8;
	enum e_nm_arch				arch:8;

	t_ftvector					sects[1];
	t_ftvector					dylibs[1];
	t_ftlist					syms[1];
};

struct			s_fileinfo
{
	int							fd;
	t_bininfo					bi[1];
};

struct			s_syminfo
{
	t_ftlist_node				node;
	char const					*strtab;
	char const					*str;
	uint8_t						n_type;
	void const					*sect;
	int16_t						n_desc;
	int64_t						n_value;
};

struct			s_acvinfo
{
	void const					*hdr;
	void const					*data;
	t_substr					filename;
	size_t						filesize;
};

struct			s_fatinfo
{
	struct fat_arch const		*hdr;
	void const					*data;
	size_t						filesize;

	/* NXArchInfo const			*local_arch; */

	/* cpu_type_t					cpu; */
	/* cpu_subtype_t				subcpu; */


	uint32_t					nfat_arch;
	int							arch_index;
};

struct			s_env
{
	unsigned int				opt;
	t_ftvector					paths;
	int64_t						(*sym_insert)();
};

int				nm_env_make(int ac, char const *const *av, t_env e[1]);

int				nm_file_make(t_env const e[1], char const *p, t_fileinfo f[1]);
void			nm_file_make_processpath(char const *file, t_substr *dst[2]);
void			nm_file_release(t_fileinfo f[1]);

void			nm_bin_readmagic(t_bininfo bi[1]);
int				nm_bin_handle(t_env const e[1], t_bininfo bi[1]);
bool			nm_bin_ckaddr(t_bininfo const bi[1], void const *ptr, size_t s);

int				nm_obj_handle(t_env const e[1], t_bininfo bi[1]);
int				nm_obj_buildindices(t_bininfo bi[1]);
int				nm_obj_symlist_build(t_env const e[1], t_bininfo bi[1]);
int				nm_obj_symlist_insert_popt(
	t_env const e[1], t_bininfo bi[1], t_syminfo const si[1]);
int				nm_obj_symlist_insert_noopt(
	t_env const e[1], t_bininfo bi[1], t_syminfo const si[1]);
int				nm_obj_symlist_insert_nopt(
	t_env const e[1], t_bininfo bi[1], t_syminfo const si[1]);
int				nm_obj_printsym(
	t_env const e[1], t_bininfo const bi[1], t_syminfo const si[1]);

int				nm_acv_handle(t_env const e[1], t_bininfo bi[1]);
int				nm_acv_read_header(t_bininfo const bi[1], t_acvinfo ai[1]);

int				nm_fat_handle(t_env const e[1], t_bininfo bi[1]);

#endif
