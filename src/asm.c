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
	glob->param = 0;
	glob->ptr = NULL;
	glob->ocp_ptr = NULL;
	glob->queue = NULL;
	glob->byte_nbr = 0;
	glob->inst_count = 0;
}
/*
static			void debug(t_asm *glob)
{
	t_list		*input;
	char		*str;
	int			i;

	input = glob->input;
	while (input)
	{
		str = ((t_input *)input->content)->bin;
		if (str)
		{
			i = 0;
			while (str[i] && i < ((t_input *)input->content)->bin_size)
			{
				ft_printf("%x%s"
				, str[i]
				, i % 2 ? " " : "");
				i++;
			}
			if (((t_input *)input->content)->type == 'c'
			|| ((t_input *)input->content)->type == 'n')
				ft_putendl("");
			ft_putendl(str);
		}
		input = input->next;
	}
}
*/

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

static void 	add_zeros(t_asm *glob, char type, int len, int fd)
{
	int		expected_len;
	int		i;

	expected_len = type == 'n' ? 132 : 2052;
	i = 0;
	while (i < expected_len - len)
	{
		ft_putchar_fd(0, fd);
		i++;
	}
	if (type == 'n')
		add_instructions_count(glob, fd);
}

static void		create_cor_file(t_asm *glob)
{
	int		fd;
	int		i;
	t_list	*input;
	char	*str;
	char	type;

	fd = open("test", O_CREAT | O_WRONLY, 0777);
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
			if (type == 'c' || type == 'n')
				add_zeros(glob, type, i, fd);
			//	add_instr_nb();
		}
		input = input->next;
	}
	close(fd);
}

int				main(int ac, char **av)
{
	t_asm	glob;

	init_asm(&glob);
	if (ac != 2 || !file_exists(av[1]))
		return (print_usage());
	if (!get_input(&glob, &glob.input, av[1]))
		return (-1); // free input, si ret == 0, print "ERROR", si =-1 print "lexical_error" Free_input(&glob.input)
	if (!lexer(&glob, &glob.input))
		return (-1); // free input
		//magic number, padding, bon nombre de zeros etc...
	create_cor_file(&glob);
	//debug(&glob);
	return (0);
}
