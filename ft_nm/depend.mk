O_FILES :=	o/srcs/bin_readmagic.o o/srcs/build_sections_vector.o \
			o/srcs/endianness.o o/srcs/env_make.o o/srcs/file_make.o \
			o/srcs/file_processpath.o o/srcs/file_release.o o/srcs/ft_arg.o \
			o/srcs/handle_file.o o/srcs/main.o

LIBS_DEPEND := libft/libft.a

libs:
	make -C libft
.PHONY: libs



MAX_SOURCE_LEN := 28
o/srcs/bin_readmagic.o: srcs/bin_readmagic.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h | o/srcs/
o/srcs/build_sections_vector.o: srcs/build_sections_vector.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h | o/srcs/
o/srcs/endianness.o: srcs/endianness.c | o/srcs/
o/srcs/env_make.o: srcs/env_make.c include/ft_nm.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	include/ft_arg.h | o/srcs/
o/srcs/file_make.o: srcs/file_make.c include/ft_nm.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
o/srcs/file_processpath.o: srcs/file_processpath.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h | o/srcs/
o/srcs/file_release.o: srcs/file_release.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h | o/srcs/
o/srcs/ft_arg.o: srcs/ft_arg.c include/ft_arg.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/libft.h | o/srcs/
o/srcs/handle_file.o: srcs/handle_file.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h | o/srcs/
o/srcs/main.o: srcs/main.c include/ft_nm.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
