/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:24:00 by pimichau          #+#    #+#             */
/*   Updated: 2019/07/03 14:26:16 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		str_isascii(char **line, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (!ft_isascii((*line)[i]))
		{
			ft_strdel(line);
			return (0);
		}
		i++;
	}
	return (1);
}
