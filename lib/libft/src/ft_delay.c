/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stin <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 03:47:47 by stin              #+#    #+#             */
/*   Updated: 2019/03/20 01:38:36 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_delay(time_t seconds)
{
	time_t		start;
	time_t		end;

	if ((start = time(NULL)) < 0)
		return (-1);
	end = start + seconds;
	while (start <= end)
	{
		if ((start = time(NULL)) < 0)
			return (-1);
	}
	return (0);
}
