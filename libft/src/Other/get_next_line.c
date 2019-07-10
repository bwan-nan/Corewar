/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:56:09 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/03 14:30:14 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static int		update_line(t_gnl *elem, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = elem->str;
	while (elem->str[i] && elem->str[i] != '\n')
		i++;
	if (i == 0)
		*line = ft_strnew(0);
	else
		*line = ft_strsub(elem->str, 0, i);
	if (ft_strchr(elem->str, '\n'))
		elem->str = ft_strdup(ft_strchr(elem->str, '\n') + 1);
	else
		elem->str = ft_strnew(0);
	ft_strdel(&tmp);
	return (1);
}

static t_list	*init_list(t_list **list, const int fd)
{
	t_gnl	new;
	t_list	*node;

	new.fd = fd;
	new.str = NULL;
	if (!(node = ft_lstnew(&new, sizeof(t_gnl))))
		return (NULL);
	ft_lstappend(list, node);
	return (node);
}

static void		del_list(void *content, size_t size)
{
	t_gnl	*elem;

	elem = (t_gnl *)content;
	if (content && size)
	{
		ft_strdel(&elem->str);
		free(content);
	}
}

static int		update_str(const int fd, char **str, t_list **list)
{
	int		ret;
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;

	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		tmp = *str;
		*str = ft_strjoin(*str, buffer);
		ft_strdel(&tmp);
		if (ft_strchr(*str, '\n'))
			break ;
	}
	if (!str_isascii(str, ret))
	{
		ft_lstdel(list, del_list);
		return (0);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*list = NULL;
	t_list			*elem;

	if (read(fd, 0, 0) == -1 || BUFF_SIZE <= 0)
		return (-1);
	elem = list;
	while (elem)
	{
		if (((t_gnl *)elem->content)->fd == fd)
			break ;
		elem = elem->next;
	}
	if (elem == NULL)
		if (!(elem = init_list(&list, fd)))
			return (-1);
	if (((t_gnl *)elem->content)->str == NULL)
		((t_gnl *)elem->content)->str = ft_strnew(0);
	if (!ft_strchr(((t_gnl *)elem->content)->str, '\n'))
		if (!update_str(fd, &(((t_gnl *)elem->content)->str), &list))
			return (-1);
	if (((t_gnl *)elem->content)->str[0])
		return (update_line(elem->content, line));
	ft_lstdel(&list, del_list);
	return (0);
}
