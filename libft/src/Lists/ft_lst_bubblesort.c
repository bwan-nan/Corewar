/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_bubblesort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:22:36 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/02 02:50:11 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lst_bubblesort(t_list *lst, int (*cmp)(void *, void *))
{
	if (!lst)
		return (NULL);
	if (lst->next && cmp(lst->content, lst->next->content) <= 0)
		lst = ft_lstswap(lst, lst->next);
	lst->next = ft_lst_bubblesort(lst->next, cmp);
	if (lst->next && cmp(lst->content, lst->next->content) <= 0)
		lst = ft_lstswap(lst, lst->next);
	lst->next = ft_lst_bubblesort(lst->next, cmp);
	return (lst);
}
