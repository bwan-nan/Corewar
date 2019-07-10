/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:55:09 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/04 18:34:04 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop(t_list **lst, t_list *target, void (*f)(void *, size_t))
{
	t_list	*previous;
	t_list	*elem;

	elem = *lst;
	previous = NULL;
	while (elem)
	{
		if (elem == target)
		{
			if (previous)
				previous->next = elem->next;
			else
				*lst = elem->next;
			ft_lstdelone(&elem, f);
			break ;
		}
		previous = elem;
		elem = elem->next;
	}
}
