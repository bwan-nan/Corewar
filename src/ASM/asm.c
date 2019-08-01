/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:44:04 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/31 13:23:17 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		print_usage(void)
{
	ft_putendl("Usage: ./asm <sourcefile.s>");
	return (1);
}

static void		init_asm(t_asm *glob)
{
	glob->input = NULL;
	glob->labels = NULL;
	glob->current_label = NULL;
	glob->param = 0;
	glob->check = 0;
	glob->ptr = NULL;
	glob->ocp_ptr = NULL;
	glob->queue = NULL;
	glob->byte_nbr = 0;
	glob->inst_count = 0;
	glob->name_length = 0;
	glob->comment_length = 0;
}

static int		ft_asm(char *file)
{
	t_asm	glob;

	init_asm(&glob);
	if (!get_input(&glob.input, file))
		return (free_program(&glob, -1));
	if (!lexing(&glob))
		return (free_program(&glob, -1));
	reorder_list(&glob.input);
	if (!create_cor_file(&glob, file))
		return (free_program(&glob, -1));
	return (free_program(&glob, 0));
}

static int		print_man(void)
{
	int			fd;
	char		*line;
	int			i;

	fd = 0;
	if ((fd = open(MAN_PATH, O_RDONLY)) < 0)
		return (-1);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (i == 0 || i == 12 || i == 24)
			ft_printf("{ul}{bold}{green}%s{nc}\n", line);
		else if (i == 26)
			ft_printf("{bold}{cyan}%s{nc}\n", line);
		else
			ft_printf("{bold}%s{nc}\n", line);
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
	if (close(fd) < 0)
		return (-1);
	return (0);
}

int				main(int ac, char **av)
{
	int i;
	int	ret;

	i = 1;
	if (ac == 1)
		return (print_usage());
	if (ac == 2 && ft_strequ(av[1], "--man"))
		print_man();
	else if (ac == 2 && !file_exists(av[1]))
		return (print_usage());
	if (ac >= 2)
	{
		while (i < ac)
		{
			if (is_asm_file(av[i]))
				ret = ft_asm(av[i]);
			i++;
		}
	}
	return (0);
}
