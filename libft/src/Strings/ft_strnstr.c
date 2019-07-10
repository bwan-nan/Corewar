/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 10:48:35 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 22:52:48 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	j = ft_strlen(needle);
	if (j == 0)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			k = 0;
			while (i + k < len && haystack[i + k]
					&& haystack[i + k] == needle[k])
				k++;
			if (k == j)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (0);
}
