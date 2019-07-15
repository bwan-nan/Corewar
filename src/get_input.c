/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:46:37 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/01 17:20:38 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int		ret_freetab(int ret, char **tab)
{
	free_tab(tab);
	return (ret);
}

static int		lexical_error(t_list **input, char *line)
{
	static int	status = 0;
	// status == 0 ? on accepte les .name et .comment
	// status == 1 ? on accepte .name et pas .comment
	// status == 2 ? on accepte .comment et pas .name
	// status == 3 ? on accepte les instructions
	if (status <= 2)
		if (!check_header((*input)->content, line, &status))
			return (1);
	else
		if (!check_label((*input)->content, line))
			return (1);
	return (0);
}

int		print_error(char *msg, int line_number)
{
	if (!line_number && !col)
		ft_putendl(msg);
	else
		ft_printf("%s at line %d.\n", msg, line_number);
	return (0);
}

static int		add_line(t_asm *glob, t_list **input,
				char *line, int line_number)
{
	t_input		new;
	t_list		*node;

	new.line = NULL;
	new.line_number = ++line_number;
	new.bin = NULL;
	new.type = 0;
	if (!(node = ft_lstnew(&new, sizeof(t_input))))
	{
		ft_strdel(&line);
		return (0);
	}
	((t_input *)node->content)->line = line;
	ft_lstprepend(input, node);
	return (1);
}

int				get_input(t_asm *glob, t_list **input, char *file)
{
	char			*line;
	int				fd;
	static int		line_number = 0;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (++line_number && ft_strlen(line) == 0)
		{
			ft_strdel(&line);
			continue ;
		}
		if (!add_line(glob, input, line, line_number))
			return (print_error(MALLOC_ERROR, 0));
		if (lexical_error(input, line))
			return (0);
	}
	close(fd);
	ft_lstrev(input);
	if (*input == NULL)
		return (print_error(EMPTY_FILE, 0));
	return (1);
}
