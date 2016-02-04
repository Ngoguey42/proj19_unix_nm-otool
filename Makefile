# Project directories

# Git submodule to init
MODULES			:= libft
# Makefiles to call
LIBS			:= ft_nm

LIBFT_LINKS		:= ft_nm/libft


# tmp
MODULE_RULES	:= $(addsuffix /.git,$(MODULES))

# Default rule
all: $(LIBFT_LINKS) $(MODULE_RULES)
	make $(LIBS)

$(LIBFT_LINKS):
	ln -s $(abspath libft) $(abspath $@)

# Init submodules
$(MODULE_RULES):
	git submodule init $(@:.git=)
	git submodule update $(@:.git=)

$(LIBS):
	make -C $(abspath $@)/

# Clean obj files
clean:

# Clean everything
fclean: clean

# Clean and make
re: fclean all

.PHONY: all clean fclean re debug rebug _debug $(LIBS)
