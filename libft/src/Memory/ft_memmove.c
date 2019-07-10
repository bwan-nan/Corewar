/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 13:44:53 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 22:52:18 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*src2;
	char	*dst2;
	size_t	i;

	i = -1;
	src2 = (char *)src;
	dst2 = (char *)dst;
	if (src2 < dst2)
		while (len--)
			dst2[len] = src2[len];
	else
		while (++i < len)
			dst2[i] = src2[i];
	return (dst);
}
