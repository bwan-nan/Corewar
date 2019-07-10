/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 03:19:49 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/02 03:40:30 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstrotate(t_list **alst)
{
	t_list	*current;
	t_list	*first;

	first = *alst;
	*alst = first->next;
	current = first;
	while (current->next)
		current = current->next;
	current->next = first;
	first->next = NULL;
}
