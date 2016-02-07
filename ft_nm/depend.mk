O_FILES :=	o/srcs/build_sections_vector.o o/srcs/env.o o/srcs/file_make.o \
			o/srcs/file_release.o o/srcs/ft_arg.o o/srcs/handle_file.o \
			o/srcs/main.o o/srcs/processpath.o

LIBS_DEPEND := libft/libft.a

libs:
	make -C libft
.PHONY: libs



MAX_SOURCE_LEN := 28
o/srcs/build_sections_vector.o: srcs/build_sections_vector.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h | o/srcs/
o/srcs/env.o: srcs/env.c include/ft_nm.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	include/ft_arg.h | o/srcs/
o/srcs/file_make.o: srcs/file_make.c include/ft_nm.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| o/srcs/
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
o/srcs/processpath.o: srcs/processpath.c include/ft_nm.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h | o/srcs/
