/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:41:58 by pimichau          #+#    #+#             */
/*   Updated: 2019/07/25 15:09:59 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		del_label(void *content, size_t size)
{
	t_label		*label;
	label = (t_label *)content;
	if (content && size)
	{
		ft_strdel(&label->name);
		free(content);
	}
}

static void		del_input(void *content, size_t size)
{
	t_input		*input;
	input = (t_input *)content;
	if (content && size)
	{
		ft_strdel(&input->line);
		ft_strdel(&input->bin);
		free(content);
	}
}

static void		del_queue(void *content, size_t size)
{
	if (content && size)
		free(content);
}

int				print_and_free(t_asm *glob, int ret, char *msg)
{
	if (glob->labels)
		ft_lstdel(&glob->labels, del_label);
	if (glob->input)
		ft_lstdel(&glob->input, del_input);
	if (glob->queue)
		ft_lstdel(&glob->queue, del_queue);
	if (msg)
		ft_putendl(msg);
	return (ret);
}
