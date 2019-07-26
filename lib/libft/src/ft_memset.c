/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 00:57:01 by fdagbert          #+#    #+#             */
/*   Updated: 2017/11/23 19:43:41 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	t_byte *ptr;

	ptr = (t_byte *)s;
	while (n > 0)
	{
		*ptr = (t_byte)c;
		ptr++;
		n--;
	}
	return (s);
}
