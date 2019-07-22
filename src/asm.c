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
	glob->queue = NULL;
	glob->byte_nbr = 0;
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

static void		create_cor_file(t_asm *glob)
{
	int		fd;
	int		i;
	t_list	*input;
	char	*str;

	fd = open("test", O_CREAT | O_WRONLY, 0777);
	input = glob->input;
	while (input)
	{
		i = 0;
		str = ((t_input *)input->content)->bin;
		if (str)
		{
			//ft_putendl(str);
			while (i < ((t_input *)input->content)->bin_size)
			{
				ft_putchar_fd(str[i], fd);
				i++;
			}
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
