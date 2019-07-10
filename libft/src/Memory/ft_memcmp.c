/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:44:43 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 22:52:18 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*s1b;
	const char	*s2b;

	i = 1;
	s1b = (const char *)s1;
	s2b = (const char *)s2;
	if (n == 0)
		return (0);
	while (i < n && (unsigned char)*s1b == (unsigned char)*s2b)
	{
		s1b++;
		s2b++;
		i++;
	}
	return ((unsigned char)*s1b - (unsigned char)*s2b);
}
