/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:46:37 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/25 14:11:29 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		add_line(t_list **input, char *line, int *line_number)
{
	t_input		new;
	t_list		*node;

	new.line = NULL;
	new.line_number = ++(*line_number);
	new.bin = NULL;
	new.bin_size = 0;
	new.type = 0;
	new.op_index = -1;
	new.label = NULL;
	if (!(node = ft_lstnew(&new, sizeof(t_input))))
	{
		ft_strdel(&line);
		return (0);
	}
	((t_input *)node->content)->line = line;
	ft_lstprepend(input, node);
	return (1);
}

int				file_exists(char *name)
{
	char	*ext;
	int		fd;

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

char		*get_file_name(char *str)
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

int				get_input(t_list **input, char *file)
{
	char			*line;
	int				fd;
	static int		line_number = 0;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (!add_line(input, line, &line_number))
			return (print_error(MALLOC_ERROR, 0));
	}
	close(fd);
	ft_lstrev(input);
	if (*input == NULL)
		return (print_error(EMPTY_FILE, 0));
	return (1);
}
