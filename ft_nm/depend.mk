O_FILES :=	o/srcs/env.o o/srcs/ft_arg.o o/srcs/main.o

LIBS_DEPEND := libft/libft.a

libs:
	make -C libft
.PHONY: libs



MAX_SOURCE_LEN := 13
o/srcs/env.o: srcs/env.c include/ft_nm.h libft/includes/ft_ctype.h \
	libft/includes/ft_macroes.h libft/includes/ft_stdio.h \
	libft/includes/ft_stdlib.h libft/includes/ft_string.h \
	libft/includes/ft_typedefs.h libft/includes/libft.h \
	libft/includes/t_bool_for_cpp_fu_42_norm_ffs.h | o/srcs/
o/srcs/ft_arg.o: srcs/ft_arg.c include/ft_arg.h libft/includes/ft_ctype.h \
	libft/includes/ft_macroes.h libft/includes/ft_stdio.h \
	libft/includes/ft_stdlib.h libft/includes/ft_string.h \
	libft/includes/ft_typedefs.h libft/includes/libft.h \
	libft/includes/t_bool_for_cpp_fu_42_norm_ffs.h | o/srcs/
o/srcs/main.o: srcs/main.c include/ft_nm.h libft/includes/ft_ctype.h \
	libft/includes/ft_macroes.h libft/includes/ft_stdio.h \
	libft/includes/ft_stdlib.h libft/includes/ft_string.h \
	libft/includes/ft_typedefs.h libft/includes/libft.h \
	libft/includes/t_bool_for_cpp_fu_42_norm_ffs.h | o/srcs/
