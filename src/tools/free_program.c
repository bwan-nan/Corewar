/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:19:38 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/25 16:54:44 by bwan-nan         ###   ########.fr       */
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

int				free_program(t_asm *glob, int ret)
{
	if (glob->labels)
		ft_lstdel(&glob->labels, del_label);
	if (glob->input)
		ft_lstdel(&glob->input, del_input);
	if (glob->queue)
		ft_lstdel(&glob->queue, del_queue);
	return (ret);
}
