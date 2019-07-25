/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:47:18 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/25 15:23:59 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	fill_queue(t_asm *glob)
{
	t_list		*elem;
	t_label		*parent;
	t_input		*node;
	int			relative_address;
	char		*byte;

	elem = glob->queue;
	while (elem)
	{
		parent = ((t_queue *)elem->content)->parent;
		node = ((t_queue *)elem->content)->node;
		relative_address = parent->byte_nbr - node->byte_nbr;
		byte = (char *)(&relative_address);
		if (((t_queue *)elem->content)->size == 4)
		{
			*(((t_queue *)elem->content)->to_complete++) = *(byte + 3);
			*(((t_queue *)elem->content)->to_complete++) = *(byte + 2);
		}
		*(((t_queue *)elem->content)->to_complete++) = *(byte + 1);
		*(((t_queue *)elem->content)->to_complete) = *byte;
		elem = elem->next;
	}
}

int		add_to_queue(t_asm *glob, t_input *input
		, t_label *label, int type)
{
	t_queue		new;
	t_list		*elem;

	new.to_complete = NULL;
	new.node = NULL;
	new.parent = NULL;
	new.size = 0;
	if (!(elem = ft_lstnew(&new, sizeof(t_queue))))
		return (0);
	((t_queue *)elem->content)->node = input;
	((t_queue *)elem->content)->parent = label;
	((t_queue *)elem->content)->to_complete = glob->ptr;
	if ((input->op_index < 8 || input->op_index == 12) && (type & T_DIR))
	{
		glob->ptr += 4;
		((t_queue *)elem->content)->size = 4;
	}
	else
	{
		glob->ptr += 2;
		((t_queue *)elem->content)->size = 2;
	}
	ft_lstprepend(&glob->queue, elem);
	return (1);
}
