/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:44:02 by fdagbert          #+#    #+#             */
/*   Updated: 2019/04/01 21:57:22 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

static int		ft_addlist(int fd, t_list **first, t_list *temp, t_list *last)
{
	if (temp)
	{
		if (!*first)
		{
			*first = temp;
			(*first)->next = NULL;
		}
		else
		{
			temp->next = *first;
			*first = temp;
		}
	}
	else
	{
		temp = *first;
		while (temp->fd != fd && (last = temp))
			temp = temp->next;
		if (temp == *first)
			*first = (*first)->next;
		else
			last->next = temp->next;
		free(temp);
	}
	return (0);
}

static int		ft_initbuff(int fd, t_list **first, char **buff)
{
	int		ret;
	t_list	*temp;

	temp = *first;
	while (temp && temp->fd != fd)
		temp = temp->next;
	if (!temp)
	{
		if (!(temp = (t_list *)malloc(sizeof(*temp))))
			return (-1);
		ft_addlist(fd, first, temp, NULL);
		ft_bzero(temp->buff, BUFF_SIZE + 1);
		temp->fd = fd;
	}
	*buff = temp->buff;
	if (!ft_strlen(*buff))
	{
		if ((ret = read(fd, *buff, BUFF_SIZE)) < 0)
			return (-1);
		if ((!fd || fd == 1 || fd == 2) && ret == 1 && **buff == '\n')
			ret = 0;
	}
	else
		ret = 1;
	return (ret);
}

static int		ft_splitendline(char *buff, char **new)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < BUFF_SIZE && buff[i] != 0 && buff[i] != '\n')
		i++;
	if (i == BUFF_SIZE || (buff[i] != '\n' && i != 0))
		ret = 1;
	if (!(*new = ft_strnew(i)))
		return (-1);
	if (!(ft_strncpy(*new, buff, i)))
		return (-1);
	if (ret)
		ft_bzero(buff, BUFF_SIZE + 1);
	else if (!(ft_strncpy(buff, buff + i + 1, BUFF_SIZE)))
		return (-1);
	return (ret);
}

static int		ft_createlinefull(char **full, char **new)
{
	char	*temp;

	temp = NULL;
	if (!*new)
		return (-1);
	else if (!*full)
	{
		*full = *new;
		*new = NULL;
	}
	else
	{
		if (!(temp = ft_strjoin(*full, *new)))
			return (-1);
		free(*new);
		*new = NULL;
		free(*full);
		*full = temp;
	}
	return (0);
}

int				ft_get_next_line(const int fd, char **line)
{
	static t_list	*first = NULL;
	char			*buff;
	char			*new;
	int				ret;
	int				next;

	buff = NULL;
	new = NULL;
	ret = 0;
	next = 1;
	if (fd < 0 || !BUFF_SIZE || (!line && !first))
		return (-1);
	if (!line)
		return (ft_addlist(fd, &first, NULL, NULL));
	*line = NULL;
	while (next)
	{
		if ((ret = ft_initbuff(fd, &first, &buff)) < 0 ||
				(next = ft_splitendline(buff, &new)) < 0 ||
				(ft_createlinefull(line, &new)) < 0)
			return (-1);
	}
	if (ft_strlen(*line) || ft_strlen(buff) || ret)
		return (1);
	return (ft_addlist(fd, &first, NULL, NULL));
}
