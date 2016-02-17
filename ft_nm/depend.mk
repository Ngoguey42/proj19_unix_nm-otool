O_FILES :=	o/srcs/acv_handle.o o/srcs/acv_read_header.o o/srcs/bin_handle.o \
			o/srcs/bin_readmagic.o o/srcs/env_make.o o/srcs/fat_handle.o \
			o/srcs/file_make.o o/srcs/file_processpath.o o/srcs/file_release.o \
			o/srcs/main.o o/srcs/obj_buildindices.o o/srcs/obj_handle.o \
			o/srcs/obj_printsym.o o/srcs/obj_symlist_build.o \
			o/srcs/obj_symlist_insert.o

LIBS_DEPEND := libft/libft.a

libs:
	make -C libft
.PHONY: libs



MAX_SOURCE_LEN := 25
o/srcs/acv_handle.o: srcs/acv_handle.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/acv_read_header.o: srcs/acv_read_header.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/bin_handle.o: srcs/bin_handle.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/bin_readmagic.o: srcs/bin_readmagic.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/env_make.o: srcs/env_make.c include/ft_nm.h libft/include/ft_ctype.h \
	libft/include/ft_list.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h libft/include/ft_arg.h \
	| o/srcs/
o/srcs/fat_handle.o: srcs/fat_handle.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/file_make.o: srcs/file_make.c include/ft_nm.h libft/include/ft_ctype.h \
	libft/include/ft_list.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h | o/srcs/
o/srcs/file_processpath.o: srcs/file_processpath.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/file_release.o: srcs/file_release.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/main.o: srcs/main.c include/ft_nm.h libft/include/ft_ctype.h \
	libft/include/ft_list.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h | o/srcs/
o/srcs/obj_buildindices.o: srcs/obj_buildindices.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/obj_handle.o: srcs/obj_handle.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/obj_printsym.o: srcs/obj_printsym.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/obj_symlist_build.o: srcs/obj_symlist_build.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/obj_symlist_insert.o: srcs/obj_symlist_insert.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_list.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
