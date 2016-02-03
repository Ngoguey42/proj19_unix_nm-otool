#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/ranlib.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/stat.h>


// 64bit + FAT binaries

// hexdump -C -n 4 a.out

// sal
#define qprintf printf

char const g_types_corresp[] = {
	[N_UNDF] = 'U',
	[N_ABS] = 'A',
};

/*
U (undefined),
A (absolute),
C  (common symbol),
I (indirect symbol)

T (text section symbol),
D (data section symbol),
B  (bss  section  symbol),
- (for debugger symbol table entries; see -a below),
S (symbol in a section other than those above), or
l : If the symbol is local  (non-external),  the symbol's  type  is  instead represented by the corresponding lowercase letter
u : A lower case u in a dynamic shared library indicates a undefined reference to a private external in another  module  in the same library.
*/

//#define MH_MAGIC    0xfeedface -> cf fa ed fe
//#define FAT_MAGIC   0xcafebabe -> ca fe ba be



/*
easy:
-(o, A), m, P

less work:
-g, u, U, j

sort:
-n -p -r

more work:
-a, x, (l, s), t

jsaispas:
-f

*/

int print_output(int n_sym, int sym_tab_off, int str_tab_off, void *ptr)
{
	int i;
	char *stringtable = ptr + str_tab_off;
	struct nlist_64 *array = ptr + sym_tab_off;
	uint64_t val;
	uint8_t type;
	uint8_t sect;

	for (i = 0; i < n_sym; i++)
	{
		val = array[i].n_value;
		type = array[i].n_type;
		sect = array[i].n_sect;

		if (array[i].n_value != 0)
			qprintf("%016llx %s\n", array[i].n_value,  stringtable + array[i].n_un.n_strx);
		else
			qprintf("%16s '%c' %s\n", "", array[i].n_sect, stringtable + array[i].n_un.n_strx);
			/* qprintf("%16s '%c' %s\n", "", array[i].n_type, stringtable + array[i].n_un.n_strx); */

	}
	qprintf("COUNT: %d\n", n_sym);
	return 0;
}

void handle_64(void *ptr)
{
	struct mach_header_64 *h = ptr;
	int ncmds = h->ncmds;
	struct load_command *lc = ptr + sizeof(*h);
	int i;
	struct symtab_command *sym;

	qprintf("ncmds %d\n", ncmds);
	qprintf("lc->cmdsize %d \n", lc->cmdsize);
	for (i = 0; i < ncmds; i++)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			printf("LC_SYMTAB\n");
			sym = (void*)lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		}
		/* else */
			/* printf("ELSE\n"); */
		lc = (void*)lc + lc->cmdsize;
	}
	return ;
}

void nm(char *ptr)
{
	uint32_t const magic_nbr = *(uint32_t*)ptr;

	if (magic_nbr == FAT_MAGIC)
		qprintf("FAT_MAGIC\n");
	if (magic_nbr == FAT_CIGAM)
		qprintf("FAT_CIGAM\n");
	if (magic_nbr == MH_MAGIC_64)
		qprintf("MH_MAGIC_64\n");
	if (magic_nbr == MH_CIGAM_64)
		qprintf("MH_CIGAM_64\n");
	if (magic_nbr == MH_MAGIC)
		qprintf("MH_MAGIC\n");
	if (magic_nbr == MH_CIGAM)
		qprintf("MH_CIGAM\n");



	if (magic_nbr == MH_MAGIC_64)
	{
		/* printf("64b\n"); */
		handle_64(ptr);
	}
	/* else */
	/* 	qprintf("NOT 64b\n"); */


	return ;
}

int							main(int ac, char *av[])
{
	qprintf("%u\n", sizeof(struct ranlib));
	assert(ac == 2);

	int const fd = open(av[1], O_RDONLY);
	int err;
	struct stat buf[1];
	char *ptr;

	assert(fd > 0);

	err = fstat(fd, buf);
	assert(err == 0);

	ptr = mmap(0, buf->st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	assert(ptr != MAP_FAILED);

	nm(ptr);

	err = munmap(ptr, buf->st_size);
	assert(err == 0);
	close(fd);
	return (0);
}
