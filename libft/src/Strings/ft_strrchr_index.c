/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:56:16 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/23 15:57:36 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strchr_index(const char *str, char c)
{
	int		i;

	i = ft_strlen(str);
	while (str[--i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}
