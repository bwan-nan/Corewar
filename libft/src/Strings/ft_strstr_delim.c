/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_delim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 19:36:45 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/03 14:38:19 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*next_word(const char *str, char delim)
{
	while (*str && *str == delim)
		str++;
	return ((char *)str);
}

char			*ft_strstr_delim(const char *haystack, const char *needle,
				char delim)
{
	char	*found;
	int		len;

	if (haystack && needle)
	{
		if (!(found = ft_strstr(haystack, needle)))
			return (NULL);
		len = ft_strlen(needle);
		if (found == haystack)
		{
			if (!haystack[len] || haystack[len] == delim)
				return (next_word(&haystack[len], delim));
		}
		else
		{
			if (*(found - 1) == delim && (!found[len] || found[len] == delim))
				return (next_word(&found[len], delim));
		}
	}
	return (0);
}
