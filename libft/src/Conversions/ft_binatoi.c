/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binatoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:37:52 by pimichau          #+#    #+#             */
/*   Updated: 2019/03/01 22:54:31 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_binatoi(char *binary)
{
	int i;
	int	len;
	int	result;

	i = 0;
	result = 0;
	len = ft_strlen(binary);
	while (i < len)
	{
		if (binary[len - 1 - i] == '1')
			result += ft_recursive_power(2, i);
		i++;
	}
	return (result);
}
