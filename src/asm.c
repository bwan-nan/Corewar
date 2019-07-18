#include "asm.h"
#include <fcntl.h>

int		print_usage(void)
{
	ft_putendl("Usage: ./asm <sourcefile.s>");
	return (1);
}

int		file_exists(char *name)
{
	char *ext;
	int  fd;

	ext = ft_strchr(name, '.');
	if (!ft_strequ(ext, ".s"))
		return (0);
	if ((fd = open(name, O_RDONLY)) == -1))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int		main(int ac, char **av)
{
	t_asm	glob;

	glob.input = NULL;
	glob.labels = NULL;
	if (ac != 2 || !file_exists(av[1]))
		return (print_usage());
	if (!get_input(glob, &glob.input, av[1]))
		return (free_input(&glob.input)); // free input, si ret == 0, print "ERROR", si =-1 print "lexical_error"
	if (!lexer(glob, &glob.input))
		return (free_input(&glob.input));
	return (0);
}
