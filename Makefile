# Project directories

# Git submodule to init
MODULES			:= libft
# Makefiles to call
DEPS			:= ft_nm  #  ft_otool
DEPS_LINKS		:= $(addsuffix .dylink,$(DEPS))

LIBFT_LINKS		:= ft_nm/libft

# tmp
MODULE_RULES	:= $(addsuffix /.git,$(MODULES))

# Default rule
all: $(LIBFT_LINKS) $(MODULE_RULES)
	make $(DEPS) $(DEPS_LINKS)

$(LIBFT_LINKS):
	ln -s $(abspath libft) $(abspath $@)

# Init submodules
$(MODULE_RULES):
	git submodule init $(@:.git=)
	git submodule update $(@:.git=)

$(DEPS):
	make -C $(abspath $@)/

%.dylink:
	ln -s $(abspath $*)/$* $(abspath $@)

# Clean obj files
clean:
	$(foreach dep, $(DEPS), make -C $(abspath $(dep))/ clean;)

# Clean everything
fclean:
	rm -rf $(DEPS_LINKS)
	$(foreach dep, $(DEPS), make -C $(abspath $(dep))/ fclean;)

# Clean and make
re: fclean all

.PHONY: all clean fclean re debug rebug _debug $(DEPS)
