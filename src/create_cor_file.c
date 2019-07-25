/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:49:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/25 14:13:59 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		add_magic_number(int fd)
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

static void		add_zeros(t_asm *glob, char type, int fd)
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

static void		write_champion_code(t_asm *glob, t_list *input, int fd)
{
	char	*str;
	char	type;
	int		i;

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
}

int				create_cor_file(t_asm *glob, char *file)
{
	int		fd;
	char	*name;

	if (!(name = get_file_name(file)))
		return (0);
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0600);
	add_magic_number(fd);
	ft_printf("Writing output program to %s\n", name);
	write_champion_code(glob, glob->input, fd);
	ft_strdel(&name);
	close(fd);
	return (1);
}
