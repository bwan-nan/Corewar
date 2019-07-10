/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islist_sorted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 04:04:41 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/05/14 16:30:26 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_islist_sorted(t_list *list, int size, int (*cmp)(void *, void *))
{
	if (!list || !list->next || size == 0)
		return (1);
	if (cmp(list->content, list->next->content) > 0)
		return (ft_islist_sorted(list->next, size - 1, cmp));
	return (0);
}
