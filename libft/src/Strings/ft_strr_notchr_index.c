/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strr_notchr_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:55:55 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 22:52:48 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strr_notchr_index(char *str, char a, char b)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i--)
	{
		if (str[i] != a && str[i] != b)
			return (i);
	}
	return (0);
}
