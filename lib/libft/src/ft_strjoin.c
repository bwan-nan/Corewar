/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:06:49 by fdagbert          #+#    #+#             */
/*   Updated: 2017/11/23 21:48:04 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *ptr;

	if (!s1 || !s2)
		return (NULL);
	ptr = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr != NULL)
	{
		ft_strcat(ptr, s1);
		ft_strcat(ptr, s2);
	}
	return (ptr);
}
