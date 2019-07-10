/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:14:49 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/04 11:39:33 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstcpy(t_list *source, int (*cpy)(void *, void *))
{
	t_list		*copy;
	t_list		*node;

	copy = NULL;
	while (source)
	{
		if (!(node = ft_lstnew(source->content, sizeof(source->content))))
			return (NULL);
		if (cpy)
			if (cpy(node->content, source->content))
				return (NULL);
		ft_lstappend(&copy, node);
		source = source->next;
	}
	return (copy);
}
