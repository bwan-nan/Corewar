/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:53:57 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/03/01 22:52:48 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		stop;
	int		len;

	i = 0;
	stop = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (needle[stop])
		stop++;
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			len = 0;
			while (len < stop && (haystack[i + len] == needle[len]))
				len++;
			if (len == stop)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
