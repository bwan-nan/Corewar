/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 08:47:04 by fdagbert          #+#    #+#             */
/*   Updated: 2019/08/01 15:41:17 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_str_is_numeric(char *str)
{
	while (*str != '\0')
	{
		if (ft_isdigit(*str))
			str++;
		else
			return (0);
	}
	return (1);
}
