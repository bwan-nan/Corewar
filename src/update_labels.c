/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_labels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:47:27 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/25 15:15:40 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	create_label(t_list **labels, char *line, int start, int len)
{
	t_label		new;
	t_list		*node;

	new.name = NULL;
	new.byte_nbr = -1;
	if (!(node = ft_lstnew(&new, sizeof(t_label))))
		return (0);
	((t_label *)node->content)->name = ft_strsub(line, start, len);
	ft_lstappend(labels, node);
	return (1);
}

static int	add_label(t_list **labels, char *line)
{
	int		i;
	int		j;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	j = 0;
	while (ft_strchr(LABEL_CHARS, line[i + j]))
		j++;
	if (line[i + j] == ':')
		return (create_label(labels, line, i, j));
	return (1);
}

int			update_labels(t_asm *glob, t_list *input, t_list **labels)
{
	char	*line;
	t_list	*node;

	node = input;
	while (node)
	{
		line = ((t_input *)node->content)->line;
		if (line && !is_empty(line) && !is_comment(line))
			if (!add_label(labels, line))
				return (0);
		node = node->next;
	}
	glob->current_label = glob->labels;
	return (1);
}
