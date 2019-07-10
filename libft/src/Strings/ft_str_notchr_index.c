/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_notchr_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:56:41 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 22:45:41 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int		ft_str_notchr_index(char *str, char a, char b)
{
	int		i;

	i = -1;
	while (++i)
	{
		if (str[i] != a && str[i] != b)
			return (i);
	}
	return (0);
}
