/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:29:41 by bwan-nan          #+#    #+#             */
/*   Updated: 2018/11/20 15:46:26 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstclr(t_list *alst)
{
	t_list *elem;

	while (alst->next)
	{
		elem = alst->next;
		free(alst);
		alst = elem;
	}
	return (NULL);
}
