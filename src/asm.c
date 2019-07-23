#include "asm.h"
#include <fcntl.h>

static int		print_usage(void)
{
	ft_putendl("Usage: ./asm <sourcefile.s>");
	return (1);
}

static int		file_exists(char *name)
{
	char *ext;
	int  fd;

	ext = ft_strrchr(name, '.');
	if (!ft_strequ(ext, ".s"))
		return (0);
	if ((fd = open(name, O_RDONLY)) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static void		init_asm(t_asm *glob)
{
	glob->input = NULL;
	glob->labels = NULL;
	glob->current_label = NULL;
	glob->param = 0;
	glob->ptr = NULL;
	glob->ocp_ptr = NULL;
	glob->queue = NULL;
	glob->byte_nbr = 0;
	glob->inst_count = 0;
	glob->name_length = 0;
	glob->comment_length = 0;
}

static void 	add_magic_nbr(int fd)
{
	ft_putchar_fd(0, fd);
	ft_putchar_fd(-22, fd);
	ft_putchar_fd(-125, fd);
	ft_putchar_fd(-13, fd);
}

static void		add_instructions_count(t_asm *glob, int fd)
{
	char	*byte;

	byte = (char *)&glob->inst_count;
	ft_putchar_fd(*(byte + 3), fd);
	ft_putchar_fd(*(byte + 2), fd);
	ft_putchar_fd(*(byte + 1), fd);
	ft_putchar_fd(*byte, fd);
}

static void 	add_zeros(t_asm *glob, char type, int fd)
{
	int		expected_len;
	int		i;
	int		len;

	len = type == 'N' ? glob->name_length : glob->comment_length;
	expected_len = type == 'N' ? 132 : 2052;
	i = 0;
	while (i < expected_len - len)
	{
		ft_putchar_fd(0, fd);
		i++;
	}
	if (type == 'N')
		add_instructions_count(glob, fd);
}

static char		*get_file_name(char *str)
{
	int		len;
	char	*name;

	len = ft_strlen(str);
	if (!(name= ft_strnew(len + 2)))
		return (NULL);
	ft_strcpy(name, str);
	name[len - 1] = 'c';
	name[len] = 'o';
	name[len + 1] = 'r';
	return (name);
}

static int		create_cor_file(t_asm *glob, char *file)
{
	int		fd;
	int		i;
	t_list	*input;
	char	*str;
	char	*name;
	char	type;

	if (!(name = get_file_name(file)))
		return (0);
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0600);
	input = glob->input;
	add_magic_nbr(fd);
	while (input)
	{
		i = 0;
		str = ((t_input *)input->content)->bin;
		if (str)
		{
			while (i < ((t_input *)input->content)->bin_size)
				ft_putchar_fd(str[i++], fd);
			type = ((t_input *)input->content)->type;
			if (type == 'C' || type == 'N')
				add_zeros(glob, type, fd);
		}
		input = input->next;
	}
	ft_strdel(&name);
	close(fd);
	return (1);
}

int				main(int ac, char **av)
{
	t_asm	glob;

	init_asm(&glob);
	if (ac != 2 || !file_exists(av[1]))
		return (print_usage());
	if (!get_input(&glob, &glob.input, av[1]))
		return (-1); // free input, si ret == 0, print "ERROR", si =-1 print "lexical_error" Free_input(&glob.input)
	//ft_putendl("------------lexer---------------");
	if (!lexer(&glob))
		return (-1); // free input
	//ft_putendl("-----------reordering-----------");
		//magic number, padding, bon nombre de zeros etc...
	reorder_list(&glob.input);
	//ft_putendl("-----------create file----------");
	if (!create_cor_file(&glob, av[1]))
		return(-1);
	//debug(&glob);
	//ft_putnbrendl(glob.byte_nbr);
	return (0);
}
