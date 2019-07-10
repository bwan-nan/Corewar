/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:43:40 by bwan-nan          #+#    #+#             */
/*   Updated: 2018/11/20 15:42:56 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_list;
	t_list *tmp;

	if (!lst || !f)
		return (NULL);
	if (!(new_list = ft_lstnew(f(lst)->content, f(lst)->content_size)))
		return (NULL);
	tmp = new_list;
	while (lst->next)
	{
		lst = lst->next;
		if (!(tmp->next = ft_lstnew(f(lst)->content, f(lst)->content_size)))
			return (ft_lstclr(new_list));
		tmp = tmp->next;
	}
	return (new_list);
}
