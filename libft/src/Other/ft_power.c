/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 20:22:57 by bwan-nan          #+#    #+#             */
/*   Updated: 2018/11/21 11:54:06 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float		ft_power(float nb, int exp)
{
	float		result;

	if (exp == 0)
		return (1);
	result = ft_power(nb, exp / 2);
	if (exp % 2 == 0)
		return (result * result);
	else
	{
		if (exp > 0)
			return (nb * result * result);
		else
			return (result * result / nb);
	}
}
