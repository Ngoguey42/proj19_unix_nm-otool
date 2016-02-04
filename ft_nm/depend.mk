O_FILES :=	o/srcs/env.o o/srcs/main.o

LIBS_DEPEND := libft/libft.a

libs:
	make -C libft
.PHONY: libs



MAX_SOURCE_LEN := 11
o/srcs/env.o: srcs/env.c include/ft_nm.h | o/srcs/
o/srcs/main.o: srcs/main.c | o/srcs/
