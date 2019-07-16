/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 23:18:18 by fdagbert          #+#    #+#             */
/*   Updated: 2017/11/23 19:43:31 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	t_byte *ptr;
	t_byte *mem;

	ptr = (t_byte *)dest;
	mem = (t_byte *)src;
	if (mem < ptr)
	{
		while (n > 0)
		{
			ptr[n - 1] = mem[n - 1];
			n--;
		}
	}
	else
		while (n > 0)
		{
			*ptr = *mem;
			ptr++;
			mem++;
			n--;
		}
	return ((void *)dest);
}
