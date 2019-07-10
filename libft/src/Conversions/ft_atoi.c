/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:55:56 by bwan-nan          #+#    #+#             */
/*   Updated: 2018/11/19 11:46:10 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_atoi(const char *nptr)
{
	int					i;
	int					j;
	int					sign;
	unsigned long long	result;

	i = 0;
	j = -1;
	sign = 1;
	result = 0;
	while (ft_iswhitespace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i + ++j]))
		result = result * 10 + nptr[i + j] - 48;
	if (j > 19 || result > 9223372036854775807)
		return (sign == -1 ? 0 : -1);
	return (sign * result);
}
